import { Inject, Injectable } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { JsonWebTokenError, TokenExpiredError } from 'jsonwebtoken';

import { ApiConfigService } from '../api-config/api-config.service';
import { AUTH_USER_SERVICE_TOKEN } from './auth.constants';
import { AccessAndRefreshTokensDto, AccessTokenDto, AuthUserDto, UpdateAccessTokenRequestDto } from './dtos';
import { InvalidRefreshTokenException } from './exceptions';
import { AccessTokenPayload, AuthUserService, RefreshTokenPayload } from './interfaces';

@Injectable()
export class AuthService {
  constructor(
    private readonly jwtService: JwtService,
    @Inject(AUTH_USER_SERVICE_TOKEN)
    private readonly userService: AuthUserService,
    private readonly configService: ApiConfigService,
  ) {}

  validate(username: string, password: string): Promise<AuthUserDto | null> {
    return this.userService.findOneByUsernameAndPassword(username, password);
  }

  async createAccessAndRefreshTokens(user: AuthUserDto): Promise<AccessAndRefreshTokensDto> {
    const accessToken = this.signAccessToken({ sub: user.id, role: user.role });
    const refreshToken = this.signRefreshToken({ sub: user.id });

    return {
      accessToken,
      refreshToken,
    };
  }

  async updateAccessToken(data: UpdateAccessTokenRequestDto): Promise<AccessTokenDto> {
    const refreshTokenPayload = this.decodeRefreshToken(data.refreshToken);
    if (!refreshTokenPayload) throw new InvalidRefreshTokenException();

    const user = await this.userService.findOneById(refreshTokenPayload.sub);
    if (!user) throw new InvalidRefreshTokenException();

    const accessToken = this.signAccessToken({
      sub: refreshTokenPayload.sub,
      role: user.role,
    });

    return { accessToken };
  }

  private signAccessToken(payload: AccessTokenPayload): string {
    return this.signToken(payload, this.configService.jwtConfig.accessTokenExpiresIn);
  }

  private signRefreshToken(payload: RefreshTokenPayload): string {
    return this.signToken(payload, this.configService.jwtConfig.refreshTokenExpiresIn);
  }

  // eslint-disable-next-line @typescript-eslint/ban-types
  private signToken(payload: object | Buffer, expiresIn: string): string {
    return this.jwtService.sign(payload, { expiresIn });
  }

  private decodeRefreshToken(token: string): RefreshTokenPayload | null {
    try {
      return this.jwtService.verify<RefreshTokenPayload>(token);
    } catch (error) {
      if (error instanceof JsonWebTokenError || error instanceof TokenExpiredError) return null;
      throw error;
    }
  }
}
