import { Component, Input, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor, NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
  selector: 'xo-radio-button',
  templateUrl: './radio-button.component.html',
  styleUrls: ['./radio-button.component.scss'],
  providers: [
    {
      provide: NG_VALUE_ACCESSOR,
      useExisting: RadioButtonComponent,
      multi: true,
    },
  ],
})
export class RadioButtonComponent implements ControlValueAccessor {
  @Output() selectedValueChange = new EventEmitter<string>();

  @Input() name: string = '';
  @Input() label: string = '';
  @Input() value: string = '';

  public selectedValue: string = '';
  public isChecked: boolean = false;
  public onChange: any = () => {};
  public onTouched: any = () => {};

  onRadioChange() {
    this.selectedValue = this.value;
    this.onChange(this.selectedValue);
    this.selectedValueChange.emit(this.selectedValue);
  }

  writeValue(value: any) {
    this.selectedValue = value;
    this.isChecked = this.value === value;
  }

  registerOnChange(fn: any) {
    this.onChange = fn;
  }

  registerOnTouched(fn: any) {
    this.onTouched = fn;
  }
}
