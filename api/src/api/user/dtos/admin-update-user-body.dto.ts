import { PickType } from '@nestjs/swagger';

import { UserDto } from './user.dto';

export class AdminUpdateUserBodyDto extends PickType(UserDto, ['email', 'role'] as const) {}
