import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { firstValueFrom } from 'rxjs';

import { HttpOptions } from '../interfaces';
import { AuthTokenService } from './auth-token.service';
import { environment } from '@env/environment';

@Injectable({
  providedIn: 'root',
})
export class ApiService {
  readonly baseUrl: string;

  constructor(private readonly authTokenService: AuthTokenService, private readonly httpClient: HttpClient) {
    this.baseUrl = environment.apiUrl;
  }

  get<T>(path: string, options?: HttpOptions): Promise<T> {
    return firstValueFrom(this.httpClient.get<T>(this.buildUrl(path), this.buildOptions(options)));
  }

  post<T>(path: string, body: any = null, options?: HttpOptions): Promise<T> {
    return firstValueFrom(this.httpClient.post<T>(this.buildUrl(path), body, this.buildOptions(options)))!;
  }

  postForm<T>(path: string, body: any = null, options?: HttpOptions): Promise<T> {
    return firstValueFrom(this.httpClient.post<T>(this.buildUrl(path), body, this.buildOptionsForm(options)))!;
  }

  put<T>(path: string, body: any = null, options?: HttpOptions): Promise<T> {
    return firstValueFrom(this.httpClient.put<T>(this.buildUrl(path), body, this.buildOptions(options)))!;
  }

  delete<T>(path: string, options?: HttpOptions): Promise<T> {
    return firstValueFrom(this.httpClient.delete<T>(`${this.buildUrl(path)}`, this.buildOptions(options)));
  }

  private buildUrl(path: string): string {
    return `${this.baseUrl}${path}`;
  }

  private buildOptions(options?: HttpOptions): Partial<HttpOptions> {
    return {
      headers: {
        Authorization: `Bearer ${this.authTokenService.getAccessToken()}`,
        'Content-Type': 'application/json',
        ...options?.headers,
      },
      ...(options?.query ? { params: options?.query } : {}),
    };
  }

  private buildOptionsForm(options?: HttpOptions): Partial<HttpOptions> {
    return {
      headers: {
        Authorization: `Bearer ${this.authTokenService.getAccessToken()}`,
        ...options?.headers,
      },
      ...(options?.query ? { params: options?.query } : {}),
    };
  }
}
