import { IsJSON, IsString, MaxLength, MinLength } from 'class-validator';

export class CreateProductConfigDto {
  @IsString()
  @MinLength(1)
  @MaxLength(16)
  readonly name: string;
}
