import { IntersectionType, PickType } from '@nestjs/swagger';
import { IsString, MaxLength, MinLength } from 'class-validator';

import { IsTrimmed } from '../../../core/common/class-validator/validators';
import { AppUserPasswordRecoveryDto } from './app-user-password-recovery.dto';
import { UserDto } from './user.dto';

export class ResetUserPasswordBodyDto extends IntersectionType(PickType(UserDto, ['email'] as const), PickType(AppUserPasswordRecoveryDto, ['code'] as const)) {
  @IsString()
  @MinLength(8)
  @MaxLength(64)
  @IsTrimmed()
  readonly password!: string;
}
