import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'xo-range',
  templateUrl: './range.component.html',
  styleUrls: ['./range.component.scss'],
})
export class RangeComponent {
  @Input('minValue') rangeMin: number = 0;
  @Input('maxValue') rangeMax: number = 400;
  @Input('floor') floor: number = 0;
  @Input('ceil') ceil: number = 400;
  @Input('step') step: number = 1;

  @Output('onRangeChange') onRangeChange: EventEmitter<any> = new EventEmitter<any>();

  public smaller: number = 0;
  public larger: number = 400;
  public left: number = 0;
  public right: number = 0;

  public onChange(): void {
    const smaller = this.rangeMin < this.rangeMax ? this.rangeMin : this.rangeMax;
    const larger = this.rangeMax > this.rangeMin ? this.rangeMax : this.rangeMin;

    this.smaller = smaller;
    this.larger = larger;
    this.left = (smaller / 400) * 100;
    this.right = 100 - (larger / 400) * 100;
  }
}
