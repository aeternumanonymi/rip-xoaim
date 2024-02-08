import {
  Component,
  EventEmitter,
  Input,
  Output,
  OnInit,
  OnDestroy,
  SimpleChanges,
  HostListener,
  Inject,
  PLATFORM_ID,
  ViewChild,
  ElementRef,
} from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';
import { Subscription } from 'rxjs';
import { isPlatformBrowser } from '@angular/common';
import Swiper, { Navigation } from 'swiper';

Swiper.use([Navigation]);

@Component({
  selector: 'xo-configs-aimbot',
  templateUrl: './configs-aimbot.component.html',
  styleUrls: ['./configs-aimbot.component.scss'],
})
export class CustomerConfigsAimbotComponent implements OnInit, OnDestroy {
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

  public form = new FormGroup({
    keyBind1: new FormControl<number>(16),
    keyBind2: new FormControl<number>(666),
    disableKey: new FormControl<number>(666),
    smoothPercentage: new FormControl<number>(12),
    offTargetApplication: new FormControl<boolean>(true),
    head: new FormControl<boolean>(true),
    body: new FormControl<boolean>(true),
    arms: new FormControl<boolean>(true),
    legs: new FormControl<boolean>(true),
    initialActivationDelay: new FormControl<number>(100),
    nextActivationDelay: new FormControl<number>(100),
    maximumAimtime: new FormControl<number>(3500),
    maximumFov: new FormControl<number>(12),
    recoilCompensation: new FormControl<number>(100),
    resetActivationDelay: new FormControl<boolean>(true),
    resetMaximumAimTime: new FormControl<boolean>(false),
    localPlayerOnGround: new FormControl<boolean>(true),
    autoSwitchTarget: new FormControl<boolean>(true),
    oppositeTargetCheck: new FormControl<boolean>(true),
    maximumFlashAlpha: new FormControl<number>(100),
    maximumVelocity: new FormControl<number>(100),
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

  public ngOnChanges(changes: SimpleChanges): void {
    const currentValue = changes['config'].currentValue;
    if (currentValue) this.form.setValue(currentValue);
  }

  public ngOnDestroy(): void {
    this.subscriptions.forEach((subscription) => {
      subscription.unsubscribe();
    });
  }
}
