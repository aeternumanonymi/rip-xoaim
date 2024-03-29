import { PickType } from '@nestjs/swagger';

import { UserDto } from './user.dto';

export class AppUpdateSelfBodyDto extends PickType(UserDto, ['email'] as const) {}
