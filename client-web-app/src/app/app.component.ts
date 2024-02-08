import { Component, NgZone, OnInit } from '@angular/core';
import { RouterService } from './services/router.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
})
export class AppComponent implements OnInit {
  public route: string = '';

  constructor(
    private readonly ngZone: NgZone,
    private readonly routerService: RouterService
  ) {}

  public ngOnInit(): void {
    (window['ngAppComponent' as any] as any) = {
      component: this,
      zone: this.ngZone,
      _setCurrentRoute: (route: string) => this.setCurrentRoute(route),
    };

    this.routerService.route$.subscribe((route: string) => {
      this.route = route;
    });
  }

  private setCurrentRoute(route: string): void {
    this.routerService.setCurrentRoute(route);
  }
}
