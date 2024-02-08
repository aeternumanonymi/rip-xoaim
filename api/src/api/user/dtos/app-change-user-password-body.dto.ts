import { IsNotEmpty, IsString, MaxLength, MinLength } from 'class-validator';

import { IsTrimmed } from '../../../core/common/class-validator/validators';

export class AppChangeUserPasswordBodyDto {
  @IsNotEmpty()
  readonly password!: string;

  @IsString()
  @MinLength(8)
  @MaxLength(64)
  @IsTrimmed()
  readonly newPassword!: string;
}
