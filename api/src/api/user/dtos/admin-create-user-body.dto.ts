import { PickType } from '@nestjs/swagger';
import { IsString, MaxLength, MinLength } from 'class-validator';

import { IsTrimmed } from '../../../core/common/class-validator/validators';
import { UserDto } from './user.dto';

export class AdminCreateUserBodyDto extends PickType(UserDto, ['username', 'email', 'role'] as const) {
  @IsString()
  @MinLength(8)
  @MaxLength(64)
  @IsTrimmed()
  readonly password!: string;
}
