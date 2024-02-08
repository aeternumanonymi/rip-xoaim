import { Component, Inject } from '@angular/core';
import { DialogRef, DIALOG_DATA } from '@angular/cdk/dialog';

@Component({
  selector: 'xo-notification',
  templateUrl: 'notification.component.html',
  styleUrls: ['./notification.component.scss'],
})
export class NotificationComponent {
  constructor(@Inject(DIALOG_DATA) public data: any, public dialogRef: DialogRef<void>) {}
}
