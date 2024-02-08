import { Dialog } from '@angular/cdk/dialog';
import { Component, Input, Output, EventEmitter, SimpleChanges } from '@angular/core';
import { virtualKeys } from '@shared/data';
import { take } from 'rxjs';
import { KeySelectionDialogComponent } from 'src/app/dialogs';

@Component({
  selector: 'xo-key-selector',
  templateUrl: './key-selector.component.html',
  styleUrls: ['./key-selector.component.scss'],
})
export class ConfigKeySelectorComponent {
  @Input('name') name: string = '';
  @Input('label') label: string = '';
  @Input('value') value: number | null = null;
  @Input('isDisabled') isDisabled: boolean = false;
  @Output('onSelectKey') onSelectKey: EventEmitter<number> = new EventEmitter();

  public keys: any[] = virtualKeys;

  constructor(private readonly dialog: Dialog) {}

  public openDialog(): void {
    if (!this.isDisabled) {
      const dialogRef = this.dialog.open(KeySelectionDialogComponent, {
        disableClose: true,
        closeOnNavigation: true,
      });

      dialogRef.closed.pipe(take(1)).subscribe((result: any) => {
        this.name = result.name as string;
        this.onSelectKey.emit(result.value as any);
      });
    }
  }

  public ngOnChanges(changes: SimpleChanges): void {
    const value = changes['value']?.currentValue;
    const item = this.keys.find((k) => k.value === value);
    if (item) this.name = item.label;
  }
}
