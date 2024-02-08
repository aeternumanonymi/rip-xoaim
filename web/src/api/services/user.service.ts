import { Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';

import { AppUserDto } from '../dtos';
import { DataResponse } from '../interfaces';
import { ApiService } from './api.service';

@Injectable({
  providedIn: 'root',
})
export class UserService {
  private meSubject = new BehaviorSubject<AppUserDto | null>(null);

  constructor(private readonly apiService: ApiService) {}

  public async refreshMe(): Promise<AppUserDto> {
    const user = await this.getMe();
    this.meSubject.next(user);
    return user;
  }

  public clearUser(): void {
    this.meSubject.next(null);
  }

  get me(): Observable<AppUserDto | null> {
    return this.meSubject.asObservable();
  }

  private async getMe(): Promise<AppUserDto> {
    const { data } = await this.apiService.get<DataResponse<AppUserDto>>('/app/users/me');
    return data;
  }
}
