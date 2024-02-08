import { Request } from 'express';

import { AuthUserDto } from '../dtos';

export interface AuthenticatedRequest extends Request {
  user: AuthUserDto;
}
