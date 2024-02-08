import { Component } from '@angular/core';
import Swiper, { Navigation } from 'swiper';

Swiper.use([Navigation]);

@Component({
  selector: 'xo-home-features',
  templateUrl: './home-features.component.html',
  styleUrls: ['./home-features.component.scss'],
})
export class HomeFeaturesComponent {
  public swiperConfig: any = {
    navigation: true,
    slidesPerView: 2,
    spaceBetween: 40,
  };
}
