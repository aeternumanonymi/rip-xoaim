import { Column, CreateDateColumn, DeleteDateColumn, Entity, OneToMany, PrimaryGeneratedColumn, UpdateDateColumn } from 'typeorm';

import { UserEmailVerificationEntity } from './user-email-verification.entity';
import { UserPasswordRecoveryEntity } from './user-password-recovery.entity';

@Entity({ name: 'users' })
export class UserEntity {
  @PrimaryGeneratedColumn()
  id!: number;

  @Column()
  role!: string;

  @Column()
  username!: string;

  @Column()
  email!: string;

  @Column({ type: 'boolean', default: false })
  emailVerified!: boolean | null;

  @Column({ select: false })
  passwordHash?: string;

  @CreateDateColumn()
  createdAt!: Date;

  @UpdateDateColumn()
  updatedAt!: Date;

  @DeleteDateColumn()
  deletedAt!: Date | null;

  @OneToMany(() => UserEmailVerificationEntity, (emailVerification) => emailVerification.user)
  emailVerifications?: UserEmailVerificationEntity[];

  @OneToMany(() => UserPasswordRecoveryEntity, (passwordRecovery) => passwordRecovery.user)
  passwordRecovery?: UserPasswordRecoveryEntity[];
}
