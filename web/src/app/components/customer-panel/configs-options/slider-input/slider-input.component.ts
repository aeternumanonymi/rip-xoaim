import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'xo-slider-input',
  templateUrl: './slider-input.component.html',
  styleUrls: ['./slider-input.component.scss'],
})
export class ConfigSliderInputComponent {
  @Input('value') value!: number | null;
  @Input('label') label: string = '';
  @Input('minValue') minValue: number = 0;
  @Input('maxValue') maxValue: number = 100;
  @Input('isDisabled') isDisabled: boolean = false;

  @Output('valueChange') valueChange: EventEmitter<number | null> = new EventEmitter();

  public onValueChange(value: number | null = null): void {
    if (value !== null) {
      this.value = value;
    }

    this.valueChange.emit(value !== null ? value : this.value);
  }
}
