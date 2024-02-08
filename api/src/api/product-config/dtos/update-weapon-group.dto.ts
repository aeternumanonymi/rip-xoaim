import { IsJSON, IsOptional, IsString, MaxLength, MinLength } from 'class-validator';

export class UpdateWeaponGroupDto {
  @IsString()
  @MinLength(1)
  @MaxLength(16)
  readonly name: string;

  @IsJSON()
  @MaxLength(1995)
  readonly weapons: any;

  @IsJSON()
  @MaxLength(10000)
  @IsOptional()
  readonly config: any;
}
