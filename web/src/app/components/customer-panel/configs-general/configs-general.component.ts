import {
  Component,
  EventEmitter,
  Input,
  Output,
  OnInit,
  OnDestroy,
  OnChanges,
  SimpleChanges,
  ViewChild,
  ElementRef,
  Inject,
  PLATFORM_ID,
  HostListener,
} from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';
import { Subscription } from 'rxjs';
import { isPlatformBrowser } from '@angular/common';
import Swiper, { Navigation } from 'swiper';

Swiper.use([Navigation]);

@Component({
  selector: 'xo-configs-general',
  templateUrl: './configs-general.component.html',
  styleUrls: ['./configs-general.component.scss'],
})
export class CustomerConfigsGeneralComponent implements OnInit, OnDestroy, OnChanges {
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
    toggleKey: new FormControl<number>(45),
    exitKey: new FormControl<number>(46),
    aimbot: new FormControl<boolean>(true),
    triggerbot: new FormControl<boolean>(true),
    soundEsp: new FormControl<boolean>(true),
    bunnyhop: new FormControl<boolean>(true),
    autoknife: new FormControl<boolean>(true),
    autostop: new FormControl<boolean>(true),
    autoKillBlockers: new FormControl<boolean>(true),
    disableNetworking: new FormControl<boolean>(false),
    loadConfigFromFile: new FormControl<boolean>(false),
    notificationsVolume: new FormControl<number>(80),
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

  private subscriptions: Subscription[] = [];
  private isBrowser: boolean = false;

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
    const currentValue = changes['config']?.currentValue;
    if (currentValue) this.form.setValue(currentValue);
  }

  public ngOnDestroy(): void {
    this.subscriptions.forEach((subscription) => {
      subscription.unsubscribe();
    });
  }

  public onSlideChange(data: any): void {
    this.currentIndex = data.realIndex;
  }
}
