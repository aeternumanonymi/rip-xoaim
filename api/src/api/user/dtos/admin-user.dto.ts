import { PickType } from '@nestjs/swagger';
import { plainToInstance } from 'class-transformer';

import { UserDto } from './user.dto';

export class AdminUserDto extends PickType(UserDto, ['id', 'username', 'email', 'emailVerified', 'passwordHash', 'role', 'createdAt', 'updatedAt'] as const) {
  constructor(args: AdminUserDto) {
    super();
    Object.assign(this, plainToInstance(AdminUserDto, args, { excludeExtraneousValues: false }));
  }
}
