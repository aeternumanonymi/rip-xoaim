import { IsJWT } from 'class-validator';

export class UpdateAccessTokenRequestDto {
  @IsJWT()
  readonly refreshToken!: string;
}
