import { Component, EventEmitter, forwardRef, Input, Output } from '@angular/core';
import { ControlValueAccessor, NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
  selector: 'xo-toggle-switch',
  templateUrl: 'toggle-switch.component.html',
  styleUrls: ['./toggle-switch.component.scss'],
  providers: [
    {
      provide: NG_VALUE_ACCESSOR,
      useExisting: forwardRef(() => ToggleSwitchComponent),
      multi: true,
    },
  ],
})
export class ToggleSwitchComponent implements ControlValueAccessor {
  @Input('isDisabled') isDisabled: boolean = false;
  @Input('isChecked') isChecked: boolean = false;
  @Output('onToggleSwitch') onToggleSwitch: EventEmitter<boolean> = new EventEmitter<boolean>();

  public onChange: any = () => {};
  public onTouched: any = () => {};

  public writeValue(value: any): void {
    this.isChecked = value;
  }

  public registerOnChange(fn: any): void {
    this.onChange = fn;
  }

  public registerOnTouched(fn: any): void {
    this.onTouched = fn;
  }

  public setDisabledState(isDisabled: boolean): void {
    this.isDisabled = isDisabled;
  }

  public onToggleSwitchChange(): void {
    this.onChange(this.isChecked);
    this.onToggleSwitch.emit(this.isChecked);
  }
}
