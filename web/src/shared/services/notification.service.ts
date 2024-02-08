import { Injectable } from '@angular/core';
import { Dialog } from '@angular/cdk/dialog';

import { NotificationComponent } from '../components';

@Injectable({
  providedIn: 'root',
})
export class NotificationService {
  constructor(private readonly dialog: Dialog) {}

  public show(text: string): void {
    this.dialog.open(NotificationComponent, {
      disableClose: true,
      closeOnNavigation: true,
      data: { text: text },
    });
  }
}
