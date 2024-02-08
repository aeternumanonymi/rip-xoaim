import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class AuthTokenService {
  private static readonly REFRESH_TOKEN_KEY = 'auth-refresh-token';

  private accessTokenValue: string | null = null;

  getAccessToken(): string | null {
    return this.accessTokenValue;
  }

  getRefreshToken(): string | null {
    return localStorage.getItem(AuthTokenService.REFRESH_TOKEN_KEY);
  }

  setAccessToken(accessToken: string): void {
    this.accessTokenValue = accessToken;
  }

  setRefreshToken(refreshToken: string): void {
    localStorage.setItem(AuthTokenService.REFRESH_TOKEN_KEY, refreshToken);
  }

  clearAccessToken(): void {
    this.accessTokenValue = null;
  }

  clearRefreshToken(): void {
    localStorage.removeItem(AuthTokenService.REFRESH_TOKEN_KEY);
  }
}
