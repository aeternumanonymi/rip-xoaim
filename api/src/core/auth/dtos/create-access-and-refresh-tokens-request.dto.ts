import { IsNotEmpty, IsString, MaxLength, MinLength } from 'class-validator';

export class CreateAccessAndRefreshTokensRequestDto {
  @IsString()
  @MinLength(3)
  @MaxLength(16)
  readonly username!: string;

  @IsString()
  @IsNotEmpty()
  readonly password!: string;
}
