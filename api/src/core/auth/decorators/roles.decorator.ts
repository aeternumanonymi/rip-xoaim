import { SetMetadata } from '@nestjs/common';

import { ROLES_METADATA_KEY } from '../auth.constants';

export const Roles = <T>(...roles: T[]) => SetMetadata(ROLES_METADATA_KEY, roles);
