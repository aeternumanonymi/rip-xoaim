import { Injectable, Type } from '@nestjs/common';
import { InjectDataSource, InjectRepository } from '@nestjs/typeorm';
import { DataSource, EntityManager, ILike, IsNull, Repository } from 'typeorm';
import * as bcrypt from 'bcrypt';
import * as crypto from 'crypto';
import * as moment from 'moment-timezone';

import { ApiConfigService } from '../../../core/api-config/api-config.service';
import { AuthUserDto } from '../../../core/auth/dtos';
import { AuthUserService } from '../../../core/auth/interfaces';
import {
  AdminCreateUserBodyDto,
  AdminUpdateUserBodyDto,
  AdminUserDto,
  AppCreateUserBodyDto,
  AppVerifyEmailBodyDto,
  AppChangeUserPasswordBodyDto,
  AppCreateUserPasswordRecoveryBodyDto,
  ResetUserPasswordBodyDto,
  AppUpdateSelfBodyDto,
  AppUserDto,
  AdminChangeUserPasswordBodyDto,
} from '../dtos';
import { UserEmailVerificationEntity, UserEntity, UserPasswordRecoveryEntity } from '../entities';
import {
  ChangeUserPasswordUnauthorizedException,
  NoPermissionsException,
  UserEmailAlreadyTaken,
  UserEmailAlreadyVerifiedException,
  UserEmailVerificationUnauthorizedException,
  UserNotFoundException,
  UserPasswordRecoveryUnauthorizedException,
} from '../exceptions';

@Injectable()
export class UserService implements AuthUserService {
  constructor(
    private readonly configService: ApiConfigService,
    @InjectDataSource()
    private readonly dataSource: DataSource,
    @InjectRepository(UserEntity)
    private readonly userRepository: Repository<UserEntity>,
    @InjectRepository(UserEmailVerificationEntity)
    private readonly emailVerificationRepository: Repository<UserEmailVerificationEntity>,
    @InjectRepository(UserPasswordRecoveryEntity)
    private readonly userPasswordRecoveryRepository: Repository<UserPasswordRecoveryEntity>,
  ) {}

  public async getMe<T>({ id }: AuthUserDto, type: Type<T>): Promise<T> {
    return this.getUser(id, type);
  }

  public async findOneById(id: number): Promise<AuthUserDto | null> {
    try {
      return await this.getUser(id, <{ new (): AuthUserDto }>AuthUserDto);
    } catch (error) {
      if (error instanceof UserNotFoundException) return null;
      throw error;
    }
  }

  public async getUser<T>(id: number, type: Type<T>, withPasswordHash?: boolean): Promise<T> {
    const user = await this.userRepository.findOne({
      where: { id },
      withDeleted: (type as unknown) === AdminUserDto,
      select: { passwordHash: withPasswordHash },
    });

    if (user) {
      return new type({ ...user });
    }

    throw new UserNotFoundException({ id });
  }

  public async findOneByUsernameAndPassword(username: string, password: string): Promise<AuthUserDto | null> {
    const user = await this.userRepository.findOne({
      where: { username },
      select: { id: true, role: true, passwordHash: true },
    });

    if (!user) return null;
    if (!(await bcrypt.compare(password, user.passwordHash))) return null;

    return new AuthUserDto({ ...user });
  }

  public async listUsers<T>(
    args: ListUsersArgs,
    limit: number | undefined,
    offset: number | undefined,
    sort: string | undefined,
    direction: 'ASC' | 'DESC' | undefined,
    type: Type<T>,
  ): Promise<{ readonly users: T[]; readonly count: number }> {
    const order = {};
    if (sort) {
      order[sort] = direction;
    } else {
      order['createdAt'] = 'ASC' || direction;
    }

    const [users, count] = await this.userRepository.findAndCount({
      where: {
        ...(args.role && { role: args.role }),
        ...(args.email && { email: ILike(args.email.replace('%2B', '+')) }),
      },
      order,
      take: limit ?? 10,
      skip: offset,
      withDeleted: (type as unknown) === AdminUserDto,
    });

    return { users: users.map((user) => new type(user)), count };
  }

  public async createUser<T>(data: AppCreateUserBodyDto | AdminCreateUserBodyDto, type: Type<T>): Promise<T> {
    try {
      // Determine user role
      const role = data instanceof AppCreateUserBodyDto ? 'user' : data.role;

      // Hash password and store user in database
      const passwordHash = await this.hashPassword(data.password);
      const { identifiers } = await this.userRepository.insert({
        ...data,
        ...(data instanceof AppCreateUserBodyDto && {
          emailVerified: false,
        }),
        passwordHash,
        role,
      });

      const userId = identifiers[0].id;

      // Send email verification email
      const user = await this.userRepository.findOneByOrFail({ id: userId });
      await this.createEmailVerification(this.emailVerificationRepository, user);

      return await this.getUser(userId, type);
    } catch (error) {
      throw error;
    }
  }

  public async resendEmailVerificationEmailToSelf({ id }: AuthUserDto): Promise<void> {
    const user = await this.userRepository.findOneBy({
      id,
      emailVerified: false,
    });

    if (!user) throw new UserEmailAlreadyVerifiedException();
    await this.createEmailVerification(this.emailVerificationRepository, user);
  }

  public async resendEmailVerificationEmailToUser(id: number): Promise<void> {
    const user = await this.userRepository.findOneBy({
      id,
      emailVerified: false,
    });

    if (!user) throw new UserEmailAlreadyVerifiedException();
    await this.createEmailVerification(this.emailVerificationRepository, user);
  }

  public async verifyEmailAddress(user: AuthUserDto, data: AppVerifyEmailBodyDto): Promise<void> {
    const entity = <UserEmailVerificationEntity>await this.emailVerificationRepository
      .createQueryBuilder('emailVerification')
      .innerJoinAndSelect('emailVerification.user', 'user', 'user.id = :id')
      .where('code = :code')
      .andWhere('expires_at >= now()')
      .andWhere('verified_at IS NULL')
      .setParameters({
        ...data,
        id: user.id,
      })
      .getOne();

    if (!entity) throw new UserEmailVerificationUnauthorizedException(data.code);

    await this.dataSource.transaction(async (transactionManager) => {
      await transactionManager
        .getRepository(UserEntity)
        .createQueryBuilder()
        .update({ emailVerified: true })
        .where({ id: entity.userId })
        .setParameters(data)
        .execute();
      await transactionManager.getRepository(UserEmailVerificationEntity).update(entity.id, { verifiedAt: () => 'now()' });
    });

    // TODO: Send email...
    // await this.emailService.sendEmail((<UserEntity>entity.user).email, 'email-verified', 'Email verification');
  }

  public async updateSelf(user: AuthUserDto, data: AppUpdateSelfBodyDto): Promise<AppUserDto> {
    const targtetUser = await this.userRepository.findOne({
      where: { id: user.id, deletedAt: IsNull() },
      select: { passwordHash: true, email: true },
    });

    if (!targtetUser) throw new UserNotFoundException({ id: user.id });
    if (targtetUser.email !== data.email) {
      const isExistingEmail = await this.userRepository.findOne({ where: { email: data.email } });
      if (isExistingEmail) {
        throw new UserEmailAlreadyTaken();
      }
    }

    await this.userRepository.update({ id: user.id }, data);
    return new AppUserDto(await this.userRepository.findOneByOrFail({ id: user.id }));
  }

  public async updateUser(id: number, authUser: AuthUserDto, data: AdminUpdateUserBodyDto): Promise<AdminUserDto> {
    const targetUser = await this.userRepository.findOne({
      where: { id, deletedAt: IsNull() },
      select: { email: true },
    });

    if (!targetUser) throw new UserNotFoundException({ id });
    if (targetUser.role === 'Admin') throw new NoPermissionsException();

    let isNewEmail = false;
    if (targetUser.email !== data.email) {
      const isExistingEmail = await this.userRepository.findOne({ where: { email: data.email } });
      if (isExistingEmail) {
        throw new UserEmailAlreadyTaken();
      }

      isNewEmail = true;
    }

    await this.userRepository.update({ id }, data);
    const user = new AdminUserDto(await this.userRepository.findOneByOrFail({ id }));

    return user;
  }

  public async restoreUser(id: number, transactionManager?: EntityManager): Promise<void> {
    return await this.setUserDeleted(id, true, transactionManager);
  }

  public async deleteUser(id: number, transactionManager?: EntityManager): Promise<void> {
    return await this.setUserDeleted(id, false, transactionManager);
  }

  public async changePassword(user: AuthUserDto, data: AppChangeUserPasswordBodyDto): Promise<void> {
    const oldUser = await this.userRepository.findOne({
      where: { id: user.id },
      select: { passwordHash: true },
    });

    if (oldUser) {
      if (!(await bcrypt.compare(data.password, oldUser.passwordHash))) {
        throw new ChangeUserPasswordUnauthorizedException();
      }

      const newPasswordHash = await this.hashPassword(data.newPassword);
      await this.userRepository
        .createQueryBuilder()
        .update({ passwordHash: newPasswordHash })
        .where({
          id: user.id,
          passwordHash: oldUser.passwordHash,
        })
        .execute();

      const entity = await this.getUser(user.id, AppUserDto);

      // TODO: Send email
      // await this.emailService.sendEmail(entity.email, 'password-changed', 'Password changed');
    }
  }

  public async changeUserPassword(id: number, data: AdminChangeUserPasswordBodyDto): Promise<void> {
    const newPasswordHash = await this.hashPassword(data.newPassword);
    await this.userRepository.createQueryBuilder().update({ passwordHash: newPasswordHash }).where({ id }).execute();
    const entity = await this.getUser(id, AppUserDto);

    // TODO: Send email
    // await this.emailService.sendEmail(entity.email, 'password-changed', 'Password changed');
  }

  public async createPasswordRecovery(data: AppCreateUserPasswordRecoveryBodyDto): Promise<void> {
    const user = await this.userRepository.findOneBy(data);
    if (!user) return;

    const code = crypto.randomUUID();
    const expiresAt = moment.utc();
    expiresAt.add('1', 'hour');

    await this.userPasswordRecoveryRepository
      .createQueryBuilder()
      .insert()
      .values({
        userId: user.id,
        code: code,
        expiresAt: expiresAt.format(),
      })
      .execute();

    // TODO: Send email...

    /*
    await this.emailService.sendEmail(user.email, 'password-recovery', 'Password recovery', {
      url: `${this.configService.apiConfig.webUrl}/account/reset-password?email=${user.email}&code=${code}`,
    });
    */
  }

  public async resetPassword(data: ResetUserPasswordBodyDto): Promise<void> {
    const entity = await this.userPasswordRecoveryRepository
      .createQueryBuilder()
      .innerJoinAndSelect('user', 'user', 'lower(user.email) = lower(:email)')
      .where('code = :code')
      .andWhere('expires_at >= now()')
      .andWhere('completed_at IS NULL')
      .setParameters(data)
      .getOne();

    if (!entity) throw new UserPasswordRecoveryUnauthorizedException(data.code);

    const passwordHash = await this.hashPassword(data.password);

    await this.dataSource.transaction(async (transactionManager) => {
      await transactionManager
        .getRepository(UserEntity)
        .createQueryBuilder()
        .update({ passwordHash })
        .where({ id: entity.userId })
        .setParameters(data)
        .execute();
      await transactionManager.getRepository(UserPasswordRecoveryEntity).update(entity.id, { completedAt: () => 'now()' });
    });

    // TODO: Send email...
    // await this.emailService.sendEmail(data.email, 'password-changed', 'Password changed');
  }

  private async createEmailVerification(emailVerificationRepository: Repository<UserEmailVerificationEntity>, user: UserEntity): Promise<void> {
    const code = crypto.randomUUID();
    const expiresAt = moment.utc();
    expiresAt.add('24', 'hours');

    await emailVerificationRepository.createQueryBuilder().insert().values({ userId: user.id, code: code, expiresAt: expiresAt.format() }).execute();

    // TODO: Send email...

    /*
    await this.emailService.sendEmail(user.email, 'verify-email', 'Email verification', {
      url: `${this.configService.apiConfig.webUrl}/account/verify-email?email=${user.email}&code=${code}`,
    });
    */
  }

  private async setUserDeleted(id: number, setDelete: boolean, transactionManager?: EntityManager): Promise<void> {
    const userRepository = transactionManager ? transactionManager.getRepository(UserEntity) : this.userRepository;
    const result = setDelete ? await userRepository.restore({ id }) : await userRepository.softDelete({ id, deletedAt: IsNull() });
    if (!result.affected) throw new UserNotFoundException({ id });
  }

  private async hashPassword(password: string): Promise<string> {
    const passwordHash = await bcrypt.hash(password, 10);

    return passwordHash;
  }

  private encryptString(text: string): string {
    let iv = crypto.randomBytes(16);
    let cipher = crypto.createCipheriv('aes-256-cbc', Buffer.from(this.configService.apiConfig.encryptionKey), iv);
    let encrypted = cipher.update(text.toString());
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    return iv.toString('hex') + ':' + encrypted.toString('hex');
  }

  private decryptString(text: string): string {
    let parts = text.split(':');
    let iv = Buffer.from(parts.shift(), 'hex');
    let encryptedText = Buffer.from(parts.join(':'), 'hex');
    let decipher = crypto.createDecipheriv('aes-256-cbc', Buffer.from(this.configService.apiConfig.encryptionKey), iv);
    let decrypted = decipher.update(encryptedText);
    decrypted = Buffer.concat([decrypted, decipher.final()]);
    return decrypted.toString();
  }
}

export interface ListUsersArgs {
  role?: string;
  email?: string;
}
