import { ViewportRuler } from '@angular/cdk/scrolling';
import {
  ChangeDetectorRef,
  Component,
  ElementRef,
  EventEmitter,
  forwardRef,
  Input,
  Output,
  ViewChild,
  OnInit,
  OnChanges,
  AfterViewInit,
} from '@angular/core';
import { NG_VALUE_ACCESSOR, ControlValueAccessor } from '@angular/forms';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';

@Component({
  selector: 'xo-select',
  templateUrl: './select.component.html',
  styleUrls: ['./select.component.scss'],
  providers: [
    {
      provide: NG_VALUE_ACCESSOR,
      useExisting: forwardRef(() => SelectComponent),
      multi: true,
    },
  ],
})
export class SelectComponent implements OnInit, AfterViewInit, OnChanges, ControlValueAccessor {
  @ViewChild('trigger', { static: true }) trigger!: ElementRef;

  @Input() selectedValue: string = '';
  @Input() hasSearch: boolean = false;
  @Input() placeholder: string = '';
  @Input() searchPlaceholder: string = '';
  @Input() options: any[] = [];
  @Input() nameField: string = '';
  @Input() valueField: string = '';
  @Input() isDisabled!: boolean;

  @Output() optionSelected = new EventEmitter<string>();

  public selectedOption: any = null;
  public showingOptions: boolean = false;
  public filteredOptions: any[] = [];
  public parentWidth: number = 0;

  public onModelChange: (value: any) => void = () => {};

  private ignoreClose: boolean = false;
  private onTouched: () => void = () => {};

  constructor(protected readonly viewportRuler: ViewportRuler, protected changeDetectorRef: ChangeDetectorRef) {
    this.viewportRuler
      .change()
      .pipe(takeUntilDestroyed())
      .subscribe(() => {
        if (this.showingOptions) {
          this.measureParentWidth();
        }
      });
  }

  public ngOnInit(): void {
    this.filteredOptions = this.options;
  }

  public ngAfterViewInit(): void {
    this.measureParentWidth();
  }

  public ngOnChanges(): void {
    this.filteredOptions = this.options;
    if (this.selectedOption) {
      const existing = this.filteredOptions.find((option) => {
        return option[this.valueField] === this.selectedOption[this.valueField];
      });

      this.selectedValue = !!existing ? existing[this.nameField] : '';
    }
  }

  public writeValue(value: any): void {
    if (value !== null && value !== undefined) {
      this.selectedOption = this.options.find((option) => option[this.valueField] === value) || null;
      if (this.selectedOption) this.selectedValue = this.selectedOption[this.nameField];
    } else {
      this.selectedValue = '';
      this.selectedOption = null;
    }
  }

  public registerOnChange(fn: (value: any) => void): void {
    this.onModelChange = fn;
  }

  public registerOnTouched(fn: () => void): void {
    this.onTouched = fn;
  }

  public toggleDropdown(): void {
    if (!this.isDisabled) {
      if (!this.showingOptions) {
        this.showOptions();
      } else {
        this.hideOptions();
      }
    }
  }

  public onSearch(event: any): void {
    const searchString = event.target.value;
    this.filterOptions(searchString);
    if (!this.showingOptions) {
      this.showOptions();
    }
  }

  public showOptions(): void {
    this.showingOptions = true;
    this.measureParentWidth();
  }

  public onBlur(): void {
    this.ignoreClose = true;
    this.onTouched();
  }

  public hideOptions(force?: boolean): void {
    if (!this.ignoreClose || force) {
      this.showingOptions = false;
    }
  }

  public selectOption(option: any = null): void {
    if (option) {
      this.selectedOption = option;
      this.selectedValue = '';

      setTimeout(() => {
        this.selectedValue = option[this.nameField];
        this.onModelChange(option[this.valueField]);
        this.optionSelected.emit(option[this.valueField]);
        this.filterOptions('');
      });
    } else {
      this.selectedOption = null;
      this.selectedValue = '';
      this.onModelChange(null);
      this.optionSelected.emit('');
    }

    this.ignoreClose = false;
    this.hideOptions();
    this.onTouched();
  }

  private filterOptions(value: string): void {
    this.filteredOptions = this.options.filter((option) => option[this.nameField].toLowerCase().includes(value.toLowerCase()));
  }

  private measureParentWidth(): void {
    if (this.trigger) {
      const rect = this.trigger.nativeElement.getBoundingClientRect();
      this.parentWidth = rect.width;
      this.changeDetectorRef.markForCheck();
      this.changeDetectorRef.detectChanges(); // BUG HERE???
    }
  }
}
