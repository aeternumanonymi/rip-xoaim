import { Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class RouterService {
  private routeSubject: BehaviorSubject<string> = new BehaviorSubject<string>(
    'login'
  );

  public route$: Observable<string> = this.routeSubject.asObservable();

  constructor() {}

  setCurrentRoute(route: string): void {
    this.routeSubject.next(route);
  }
}
