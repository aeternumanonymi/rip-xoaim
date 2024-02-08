import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot } from '@angular/router';
import { filter, map, Observable, tap } from 'rxjs';

import { AuthService } from '@api/services';

@Injectable({
  providedIn: 'root',
})
export class GuestGuard implements CanActivate {
  constructor(private readonly authService: AuthService, private readonly router: Router) {}

  canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): Observable<boolean> {
    return this.authService.loggedIn.pipe(
      filter((value): value is boolean => value != null),
      tap((value) => !value || this.router.navigateByUrl('/')),
      map((value) => !value),
    );
  }
}
