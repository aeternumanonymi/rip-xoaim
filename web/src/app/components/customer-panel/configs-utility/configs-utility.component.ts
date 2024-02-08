import { isPlatformBrowser } from '@angular/common';
import { Component, Input, Output, EventEmitter, OnInit, OnDestroy, SimpleChanges, HostListener, Inject, PLATFORM_ID } from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';
import { Subscription } from 'rxjs';
import Swiper, { Navigation } from 'swiper';

Swiper.use([Navigation]);

@Component({
  selector: 'xo-configs-utility',
  templateUrl: './configs-utility.component.html',
  styleUrls: ['./configs-utility.component.scss'],
})
export class CustomerConfigsUtilityComponent implements OnInit, OnDestroy {
  @Input('canEdit') canEdit: boolean = false;
  @Input('config') config: any = {};
  @Output('onConfigChange') onConfigChange: EventEmitter<any> = new EventEmitter<any>();
  @HostListener('window:resize', ['$event'])
  public onResize(): void {
    if (this.isBrowser) {
      this.isDesktop = window.innerWidth >= 1380;
    }
  }

  public form = new FormGroup({
    bunnyhopKey: new FormControl<number>(32), // Spacebar
    autoknifeKey: new FormControl<number>(603), // Mouse 4
    autostopKey: new FormControl<number>(18), // Alt
  });

  public swiperConfig: any = {
    navigation: true,
    slidesPerView: 1,
    spaceBetween: 40,
    breakpoints: {
      1380: {
        slidesPerView: 3,
        spaceBetween: 0,
      },
    },
  };

  public currentIndex: number = 0;
  public isDesktop: boolean = false;

  private swiper?: Swiper;

  private isBrowser: boolean = false;
  private subscriptions: Subscription[] = [];

  constructor(@Inject(PLATFORM_ID) platformId: Object) {
    this.isBrowser = isPlatformBrowser(platformId);
  }

  public ngOnInit(): void {
    const subscription = this.form.valueChanges.subscribe((formData) => {
      this.onConfigChange.emit(formData);
    });

    if (this.isBrowser) {
      this.isDesktop = window.innerWidth >= 1380;
    }

    this.subscriptions.push(subscription);
  }

  public ngOnDestroy(): void {
    this.subscriptions.forEach((subscription) => {
      subscription.unsubscribe();
    });
  }

  public ngOnChanges(changes: SimpleChanges): void {
    const currentValue = changes['config'].currentValue;
    if (currentValue) this.form.setValue(currentValue);
  }

  public onSlideChange(data: any): void {}
}
