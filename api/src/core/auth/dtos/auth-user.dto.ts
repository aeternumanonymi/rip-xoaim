import { Expose, plainToInstance } from 'class-transformer';

export class AuthUserDto {
  @Expose()
  readonly id!: number;

  @Expose()
  readonly role!: string;

  constructor(args: AuthUserDto) {
    Object.assign(this, plainToInstance(AuthUserDto, args, { excludeExtraneousValues: true }));
  }
}
