import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AppUserDto } from '@api/dtos';
import { AuthService, UserService } from '@api/services';
import { MobileMenuService } from '@shared/services';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';
import { Dialog } from '@angular/cdk/dialog';
import { LoginDialogComponent } from 'src/app/dialogs';

@Component({
  selector: 'xo-mobile-menu',
  templateUrl: './mobile-menu.component.html',
  styleUrls: ['./mobile-menu.component.scss'],
})
export class MobileMenuComponent {
  public isMenuOpen: boolean = false;
  public me: AppUserDto | null = null;

  constructor(
    private readonly mobileMenuService: MobileMenuService,
    private readonly userService: UserService,
    private readonly authService: AuthService,
    private readonly router: Router,
    private readonly dialog: Dialog,
  ) {
    this.mobileMenuService.status.pipe(takeUntilDestroyed()).subscribe((isOpen: boolean) => {
      this.isMenuOpen = isOpen;
    });

    this.userService.me.pipe(takeUntilDestroyed()).subscribe((me) => {
      this.me = me;
    });
  }

  public toggleMenu(): void {
    this.mobileMenuService.toggleVisibility();
  }

  public openLogin(): void {
    this.toggleMenu();
    this.dialog.open(LoginDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      panelClass: 'login-dialog',
    });
  }

  public logOut(): void {
    this.authService.logOut();
    this.router.navigateByUrl('/');
    this.toggleMenu();
  }
}
