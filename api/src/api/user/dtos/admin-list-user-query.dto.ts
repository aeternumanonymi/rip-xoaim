import { Type } from 'class-transformer';
import { IsDate, IsInt, IsOptional, IsString, Max, Min } from 'class-validator';

export class AdminListUserQueryDto {
  @IsOptional()
  readonly role?: string;

  @IsString()
  @IsOptional()
  readonly email?: string;

  @Type(() => Date)
  @IsDate()
  @IsOptional()
  readonly updatedFrom?: Date;

  @Type(() => Date)
  @IsDate()
  @IsOptional()
  readonly updatedTo?: Date;

  @Type(() => Number)
  @IsInt()
  @Min(1)
  @Max(100)
  @IsOptional()
  readonly limit?: number;

  @Type(() => Number)
  @IsInt()
  @Min(0)
  @IsOptional()
  readonly offset?: number;

  @IsString()
  @IsOptional()
  readonly sort?: string;

  @IsString()
  @IsOptional()
  readonly direction?: 'ASC' | 'DESC';
}
