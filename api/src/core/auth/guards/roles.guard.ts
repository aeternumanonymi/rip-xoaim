import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Reflector } from '@nestjs/core';

import { AuthenticatedRequest } from '../../auth/interfaces';
import { ROLES_METADATA_KEY } from '../auth.constants';

@Injectable()
export class RolesGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate<T>(context: ExecutionContext): boolean {
    const roles = this.reflector.getAllAndMerge<string[]>(ROLES_METADATA_KEY, [context.getClass(), context.getHandler()]);
    if (!roles || !roles.length) return true;

    const request = <AuthenticatedRequest>context.switchToHttp().getRequest();
    const user = request.user;

    return roles.includes(user.role);
  }
}
