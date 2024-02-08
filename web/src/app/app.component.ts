import { isPlatformBrowser } from '@angular/common';
import { Component, Inject, PLATFORM_ID } from '@angular/core';
import { NavigationEnd, NavigationStart, Router } from '@angular/router';
import * as FontFaceObserver from 'fontfaceobserver';
import { filter } from 'rxjs';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';

import { MobileMenuService } from '@shared/services';

@Component({
  selector: 'xo-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
})
export class AppComponent {
  public isMobileMenuOpen: boolean = false;
  public isAdminPage: boolean = true;
  public isLoginPage: boolean = false;

  private lastRoute: string = '';
  private isBrowser: boolean = false;

  constructor(
    @Inject(PLATFORM_ID) platformId: Object,
    private readonly mobileMenuService: MobileMenuService,
    private readonly router: Router,
  ) {
    this.isBrowser = isPlatformBrowser(platformId);

    if (this.isBrowser) {
      const font = new FontFaceObserver('Oxanium');
      font.load().then(() => {
        document.body.classList.add('font-loaded');
      });
    }

    this.mobileMenuService.status.pipe(takeUntilDestroyed()).subscribe((isOpen) => {
      this.isMobileMenuOpen = isOpen;
    });

    this.router.events
      .pipe(
        takeUntilDestroyed(),
        filter((e) => e instanceof NavigationStart),
      )
      .subscribe(() => {
        this.mobileMenuService.toggleVisibility(false);
      });

    this.router.events
      .pipe(
        takeUntilDestroyed(),
        filter((e) => e instanceof NavigationEnd),
      )
      .subscribe((e: any) => {
        const route = e.url.split('?')[0];
        if (this.lastRoute !== route) {
          if (this.isBrowser) {
            window.scrollTo({ top: 0 });
          }

          this.lastRoute = route;
        }
      });

    this.router.events
      .pipe(
        takeUntilDestroyed(),
        filter((e) => e instanceof NavigationEnd),
      )
      .subscribe(() => {
        this.isAdminPage = this.router.url.includes('/admin');
        this.isLoginPage = this.router.url.includes('/account/login');
      });
  }

  get isPlainPage(): boolean {
    return this.isLoginPage || this.isAdminPage;
  }
}
