import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { readFileSync } from 'fs';
import { join } from 'path';

import { AuthUserDto } from '../dtos';
import { AccessTokenPayload } from '../interfaces';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor() {
    super({
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      secretOrKey: readFileSync(join(__dirname, '../../../../jwt-keys/private.key')),
    });
  }

  validate(payload: AccessTokenPayload): AuthUserDto {
    return { id: payload.sub, role: payload.role };
  }
}
