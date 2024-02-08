import { PickType } from '@nestjs/swagger';

import { UserDto } from './user.dto';

export class AppCreateUserPasswordRecoveryBodyDto extends PickType(UserDto, ['email'] as const) {}
