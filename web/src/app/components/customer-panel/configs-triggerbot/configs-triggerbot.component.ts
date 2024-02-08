import {
  Component,
  Input,
  Output,
  EventEmitter,
  SimpleChanges,
  ViewChild,
  ElementRef,
  HostListener,
  OnInit,
  OnChanges,
  OnDestroy,
  Inject,
  PLATFORM_ID,
} from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';
import { Subscription } from 'rxjs';
import { isPlatformBrowser } from '@angular/common';
import Swiper, { Navigation } from 'swiper';

Swiper.use([Navigation]);

@Component({
  selector: 'xo-configs-triggerbot',
  templateUrl: './configs-triggerbot.component.html',
  styleUrls: ['./configs-triggerbot.component.scss'],
})
export class CustomerConfigsTriggerbotComponent implements OnInit, OnChanges, OnDestroy {
  @ViewChild('swiperContainer') swiperContainer!: ElementRef;

  @Input('canEdit') canEdit: boolean = false;
  @Input('config') config: any = {};

  @Output('onConfigChange') onConfigChange: EventEmitter<any> = new EventEmitter<any>();

  @HostListener('window:resize', ['$event'])
  public onResize(): void {
    if (this.isBrowser) {
      this.isDesktop = window.innerWidth >= 1380;
    }
  }

  constructor(@Inject(PLATFORM_ID) platformId: Object) {
    this.isBrowser = isPlatformBrowser(platformId);
  }

  public form = new FormGroup({
    keyBind1: new FormControl<number>(18),
    keyBind2: new FormControl<number>(666),
    disableKey: new FormControl<number>(666),
    head: new FormControl<boolean>(true),
    body: new FormControl<boolean>(true),
    arms: new FormControl<boolean>(true),
    legs: new FormControl<boolean>(true),
    visibilityDelay: new FormControl<number>(100),
    hitchance: new FormControl<number>(75),
    maximumFlashAlpha: new FormControl<number>(25),
    localPlayerOnGround: new FormControl<boolean>(true),
    oppositeTargetCheck: new FormControl<boolean>(true),
    minimumDelay: new FormControl<number>(140),
    maximumDelay: new FormControl<number>(180),
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

  private isBrowser: boolean = false;
  private subscriptions: Subscription[] = [];

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
