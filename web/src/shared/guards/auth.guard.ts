import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot } from '@angular/router';
import { filter, Observable, switchMap, tap, of } from 'rxjs';
import { catchError } from 'rxjs/operators';

import { AuthService, UserService } from '@api/services';
import { AppUserDto } from '@api/dtos';
import { Dialog } from '@angular/cdk/dialog';
import { LoginDialogComponent } from 'src/app/dialogs';

@Injectable({
  providedIn: 'root',
})
export class AuthGuard implements CanActivate {
  constructor(
    private readonly authService: AuthService,
    private readonly userService: UserService,
    private readonly router: Router,
    private readonly dialog: Dialog,
  ) {}

  canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): Observable<boolean> {
    const requiredRole = route.data['requiredRole'];

    return this.authService.loggedIn.pipe(
      filter((value): value is boolean => value != null),
      switchMap((loggedIn) => {
        if (loggedIn && !requiredRole) {
          return of(true);
        } else if (loggedIn && requiredRole) {
          return this.userService.me.pipe(
            tap((me: AppUserDto | null) => {
              if (requiredRole && me?.role !== requiredRole) {
                this.router.navigate(['/account/login'], { queryParams: { returnUrl: state.url } });
                throw new Error('Unauthorized');
              }
            }),
            switchMap(() => of(true)),
            catchError(() => {
              return of(false);
            }),
          );
        }
        this.openLogin(state.url);
        return of(false);
      }),
    ) as Observable<boolean>;
  }

  private openLogin(postLoginUrl: string): void {
    const dialogRef = this.dialog.open(LoginDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      panelClass: 'login-dialog',
    });

    dialogRef.closed.subscribe((success) => {
      if (success) {
        this.router.navigate([postLoginUrl]);
      }
    });
  }
}
