export class AppUserDto {
  readonly id!: number;
  readonly username!: string;
  readonly email!: string;
  readonly emailVerified!: boolean | null;
  readonly role!: string;
  readonly createdAt!: Date;
  readonly updatedAt!: Date;
}
