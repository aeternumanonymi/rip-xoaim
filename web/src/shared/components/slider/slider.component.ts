import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'xo-slider',
  templateUrl: './slider.component.html',
  styleUrls: ['./slider.component.scss'],
})
export class SliderComponent {
  @Input('value') value: number | null = null;
  @Input('minValue') min: number = 0;
  @Input('maxValue') max: number = 100;
  @Input('step') step: number = 1;
  @Input('isDisabled') isDisabled: boolean = false;

  @Output('onRangeChange') onRangeChange: EventEmitter<any> = new EventEmitter<any>();

  public onChange(): void {
    this.onRangeChange.emit(this.value);
  }
}
