import { PickType } from '@nestjs/swagger';
import { Expose, plainToInstance } from 'class-transformer';
import { IsArray } from 'class-validator';

import { UserDto } from './user.dto';

export class AppUserDto extends PickType(UserDto, ['id', 'username', 'email', 'emailVerified', 'role', 'createdAt', 'updatedAt'] as const) {
  constructor(args: AppUserDto) {
    super();
    Object.assign(this, plainToInstance(AppUserDto, args, { excludeExtraneousValues: true }));
  }
}
