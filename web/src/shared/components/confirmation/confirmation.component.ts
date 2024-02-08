import { Component, Inject } from '@angular/core';
import { DialogRef, DIALOG_DATA } from '@angular/cdk/dialog';

@Component({
  selector: 'xo-confirmation',
  templateUrl: 'confirmation.component.html',
  styleUrls: ['./confirmation.component.scss'],
})
export class ConfirmationComponent {
  constructor(@Inject(DIALOG_DATA) public data: any, public dialogRef: DialogRef<boolean>) {}
}
