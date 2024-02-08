import { Component, Input, forwardRef } from '@angular/core';
import { ControlValueAccessor, NG_VALUE_ACCESSOR, FormControl } from '@angular/forms';

@Component({
  selector: 'xo-switch',
  templateUrl: './switch.component.html',
  styleUrls: ['./switch.component.scss'],
  providers: [
    {
      provide: NG_VALUE_ACCESSOR,
      useExisting: forwardRef(() => ConfigSwitchComponent),
      multi: true,
    },
    {
      provide: FormControl,
      useExisting: forwardRef(() => ConfigSwitchComponent),
      multi: false,
    },
  ],
})
export class ConfigSwitchComponent implements ControlValueAccessor {
  @Input('label') label: string = '';
  @Input('isDisabled') isDisabled: boolean = false;

  public isChecked: boolean = false;
  public onModelChange: (value: any) => void = () => {};

  public writeValue(value: any): void {
    this.isChecked = value;
  }

  public registerOnChange(fn: (value: any) => void): void {
    this.onModelChange = fn;
  }

  public registerOnTouched(fn: () => void): void {
    // NOT NECESSARY
  }

  public onToggleSwitch(value: boolean): void {
    this.onModelChange(value);
  }
}
