import { isPlatformBrowser } from '@angular/common';
import { Component, Inject, PLATFORM_ID } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService, UserService } from '@api/services';
import { AppUserDto } from '@api/dtos';
import { MobileMenuService } from '@shared/services';
import { LoginDialogComponent } from '../../dialogs';
import { Dialog } from '@angular/cdk/dialog';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';

@Component({
  selector: 'xo-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.scss'],
})
export class HeaderComponent {
  public isMobileMenuVisible: boolean = false;
  public showUserDropdown: boolean = false;
  public isLoggedIn: boolean = false;
  public me: AppUserDto | null = null;

  private isBrowser: boolean = false;

  constructor(
    private readonly authService: AuthService,
    private readonly userService: UserService,
    private readonly mobileMenuService: MobileMenuService,
    private readonly router: Router,
    private readonly dialog: Dialog,
    @Inject(PLATFORM_ID) platformId: Object,
  ) {
    this.isBrowser = isPlatformBrowser(platformId);

    this.authService.loggedIn.pipe(takeUntilDestroyed()).subscribe((isLoggedIn) => {
      this.isLoggedIn = !!isLoggedIn;
    });

    this.userService.me.pipe(takeUntilDestroyed()).subscribe((me) => {
      this.me = me;
    });

    this.mobileMenuService.status.pipe(takeUntilDestroyed()).subscribe((status) => {
      this.isMobileMenuVisible = status;
    });
  }

  public openLogin(): void {
    this.dialog.open(LoginDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      panelClass: 'login-dialog',
    });
  }

  public toggleMobileMenu(): void {
    this.mobileMenuService.toggleVisibility();
  }

  public logOut(): void {
    this.authService.logOut();
    this.router.navigateByUrl('/');
  }
}
