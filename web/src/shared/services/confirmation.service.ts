import { Injectable } from '@angular/core';
import { Dialog, DialogRef } from '@angular/cdk/dialog';

import { ConfirmationComponent } from '../components';

@Injectable({
  providedIn: 'root',
})
export class ConfirmationService {
  constructor(private readonly dialog: Dialog) {}

  public show(text: string, submitText: string, cancelText: string): DialogRef<unknown, ConfirmationComponent> {
    return this.dialog.open(ConfirmationComponent, {
      disableClose: true,
      closeOnNavigation: true,
      data: {
        text: text,
        submitText: submitText,
        cancelText: cancelText,
      },
    });
  }
}
