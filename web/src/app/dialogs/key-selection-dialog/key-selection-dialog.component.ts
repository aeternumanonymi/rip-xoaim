import { DialogRef } from '@angular/cdk/dialog';
import { Component } from '@angular/core';
import { virtualKeys } from '@shared/data';

@Component({
  selector: 'xo-key-selection-dialog',
  templateUrl: 'key-selection-dialog.component.html',
  styleUrls: ['./key-selection-dialog.component.scss'],
})
export class KeySelectionDialogComponent {
  public keys: any[] = virtualKeys;

  public selectedKeyValue!: number;

  constructor(public readonly dialogRef: DialogRef<any>) {}

  public saveKey(): void {
    const key = this.keys.find((k) => k.value === this.selectedKeyValue);
    if (key) {
      this.dialogRef.close({
        name: key.label,
        value: key.value,
      });
    }
  }
}
