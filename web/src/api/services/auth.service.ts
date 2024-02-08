import { isPlatformBrowser } from '@angular/common';
import { HttpErrorResponse, HttpStatusCode } from '@angular/common/http';
import { Inject, Injectable, PLATFORM_ID } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';

import { InvalidCredentialsException, InvalidRefreshTokenException } from '../exceptions';
import { DataResponse } from '../interfaces';
import { ApiService } from './api.service';
import { AuthTokenService } from './auth-token.service';
import { UserService } from './user.service';

@Injectable({
  providedIn: 'root',
})
export class AuthService {
  private loggedInSubject = new BehaviorSubject<boolean | null>(null);
  private refreshTimeoutId: number | null = null;
  private isBrowser: boolean = false;

  constructor(
    private readonly apiService: ApiService,
    private readonly authTokenService: AuthTokenService,
    private readonly userService: UserService,
    @Inject(PLATFORM_ID) platformId: Object,
  ) {
    this.isBrowser = isPlatformBrowser(platformId);

    let refreshToken = this.isBrowser ? this.authTokenService.getRefreshToken() : null;
    if (refreshToken) {
      this.refresh(refreshToken);
    } else {
      this.loggedInSubject.next(false);
    }
  }

  get loggedIn(): Observable<boolean | null> {
    return this.loggedInSubject.asObservable();
  }

  public async logIn(username: string, password: string): Promise<void> {
    const { data } = await this.createAccessAndRefreshTokens(username, password);
    this.authTokenService.setAccessToken(data.accessToken);
    if (this.isBrowser) {
      this.authTokenService.setRefreshToken(data.refreshToken);
    }

    await this.userService.refreshMe();
    this.loggedInSubject.next(true);
    this.createRefreshTimeout(data.accessToken, data.refreshToken);
  }

  public logOut(): void {
    this.clearRefreshTimeout();
    this.authTokenService.clearAccessToken();
    if (this.isBrowser) {
      this.authTokenService.clearRefreshToken();
    }

    this.loggedInSubject.next(false);
    this.userService.clearUser();
  }

  private async createAccessAndRefreshTokens(username: string, password: string): Promise<DataResponse<AccessAndRequestTokens>> {
    try {
      return await this.apiService.post<DataResponse<AccessAndRequestTokens>>('/auth', {
        username,
        password,
      });
    } catch (e) {
      if (e instanceof HttpErrorResponse && e.status === HttpStatusCode.Unauthorized) throw new InvalidCredentialsException();
      throw e;
    }
  }

  private createRefreshTimeout(accessToken: string, refreshToken: string): void {
    const accessTokenPayload = this.decodeJwt<AccessTokenPayload>(accessToken);
    if (this.isBrowser) {
      this.refreshTimeoutId = window.setTimeout(
        () => this.refresh(refreshToken),
        (accessTokenPayload.exp - Math.floor(Date.now() / 1000) - 60) * 1000,
      );
    }
  }

  private async refresh(refreshToken: string): Promise<void> {
    try {
      const refreshTokenPayload = this.decodeJwt<RefreshTokenPayload>(refreshToken);
      if (refreshTokenPayload.exp < Math.floor(Date.now() / 1000)) return this.logOut();

      const { data } = await this.updateAccessToken(refreshToken);
      this.authTokenService.setAccessToken(data.accessToken);
      await this.userService.refreshMe();
      if (!this.loggedInSubject.value) {
        this.loggedInSubject.next(true);
      }
      this.createRefreshTimeout(data.accessToken, refreshToken);
    } catch (e) {
      this.loggedInSubject.next(false);
      if (e instanceof InvalidRefreshTokenException) return this.logOut();
      throw e;
    }
  }

  private decodeJwt<T>(jwt: string): T {
    const encodedPayload = jwt.split('.')[1];
    const decodedPayload = atob(encodedPayload);
    return JSON.parse(decodedPayload);
  }

  private clearRefreshTimeout(): void {
    if (!this.refreshTimeoutId) return;
    if (this.isBrowser) {
      window.clearTimeout(this.refreshTimeoutId);
    }

    this.refreshTimeoutId = null;
  }

  private async updateAccessToken(refreshToken: string): Promise<DataResponse<AccessToken>> {
    try {
      return await this.apiService.put<DataResponse<AccessAndRequestTokens>>('/auth', { refreshToken });
    } catch (e) {
      if (e instanceof HttpErrorResponse && e.status === HttpStatusCode.Unauthorized) throw new InvalidRefreshTokenException();
      throw e;
    }
  }
}

interface AccessAndRequestTokens {
  readonly accessToken: string;
  readonly refreshToken: string;
}

interface AccessToken {
  readonly accessToken: string;
}

interface AccessTokenPayload {
  readonly sub: number;
  readonly exp: number;
  readonly iat: number;
  readonly role: string;
}

interface RefreshTokenPayload {
  readonly sub: number;
  readonly exp: number;
  readonly iat: number;
}
