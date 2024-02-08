import { isPlatformBrowser } from '@angular/common';
import {
  Component,
  Input,
  Output,
  EventEmitter,
  OnInit,
  OnDestroy,
  OnChanges,
  SimpleChanges,
  HostListener,
  Inject,
  PLATFORM_ID,
} from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';
import { Subscription } from 'rxjs';
import Swiper, { Navigation } from 'swiper';

Swiper.use([Navigation]);

@Component({
  selector: 'xo-configs-sound-esp',
  templateUrl: './configs-sound-esp.component.html',
  styleUrls: ['./configs-sound-esp.component.scss'],
})
export class CustomerConfigsSoundESPComponent implements OnInit, OnDestroy, OnChanges {
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
    alwaysActive: new FormControl<boolean>(false),
    nonVisiblePlayersOnly: new FormControl<boolean>(true),
    keyBind1: new FormControl<number>(666),
    keyBind2: new FormControl<number>(666),
    disableKey: new FormControl<number>(666),
    maximumFov: new FormControl<number>(60),
    volumeLevel: new FormControl<number>(100),
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

  public isDesktop: boolean = false;
  public currentIndex: number = 0;

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

  public onSlideChange(data: any): void {
    this.currentIndex = data.realIndex;
  }
}
