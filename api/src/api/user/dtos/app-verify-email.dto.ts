import { IsUUID } from 'class-validator';

export class AppVerifyEmailBodyDto {
  @IsUUID()
  readonly code!: string;
}
