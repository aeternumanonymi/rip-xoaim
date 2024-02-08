import { DialogRef } from '@angular/cdk/dialog';
import { Component } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { AuthService } from '@api/services';

@Component({
  selector: 'xo-login-dialog',
  templateUrl: 'login-dialog.component.html',
  styleUrls: ['./login-dialog.component.scss'],
})
export class LoginDialogComponent {
  public form = new FormGroup({
    username: new FormControl<string>('', [
      Validators.required,
      Validators.minLength(3),
      Validators.maxLength(16),
      Validators.pattern('^[a-zA-Z0-9-]+$'),
    ]),
    password: new FormControl<string>('', [Validators.required, Validators.minLength(6), Validators.maxLength(16)]),
  });

  public loginError: boolean = false;

  constructor(public dialogRef: DialogRef<boolean>, private readonly authService: AuthService) {}

  public async signIn(): Promise<void> {
    const username = this.form.controls.username.value;
    const password = this.form.controls.password.value;

    if (username && password) {
      this.loginError = false;

      try {
        await this.authService.logIn(username, password);
        this.dialogRef.close(true);
      } catch (error) {
        this.loginError = true;
      }
    }
  }
}
