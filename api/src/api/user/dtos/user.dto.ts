import { Expose, Type } from 'class-transformer';
import { IsEmail, IsString } from 'class-validator';

export class UserDto {
  @Expose()
  readonly id!: number;

  @Expose()
  role!: string;

  @Expose()
  @IsString()
  username!: string;

  @Expose()
  @IsEmail()
  email!: string;

  @Expose()
  @IsString()
  passwordHash?: string;

  @Expose()
  readonly emailVerified!: boolean | null;

  @Type(() => Date)
  @Expose()
  readonly createdAt!: Date;

  @Type(() => Date)
  @Expose()
  readonly updatedAt!: Date;

  @Type(() => Date)
  @Expose()
  readonly deletedAt!: Date | null;
}
