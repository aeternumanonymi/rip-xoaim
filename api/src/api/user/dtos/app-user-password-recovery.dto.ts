import { Expose } from 'class-transformer';
import { IsUUID } from 'class-validator';

import { UserDto } from './user.dto';

export class AppUserPasswordRecoveryDto {
  readonly id!: number;

  readonly userId!: number;

  readonly user!: UserDto;

  @Expose()
  @IsUUID()
  readonly code!: string;

  readonly createdAt!: Date;

  readonly expiresAt!: Date;
}
