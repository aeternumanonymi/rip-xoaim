import { Component } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';

declare var authenticate: (credentials: string) => void;
declare var openLinkInBrowser: (link: string) => void;

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss'],
})
export class LoginComponent {
  public form = new FormGroup({
    username: new FormControl<string>('', [Validators.required, Validators.minLength(3), Validators.maxLength(16)]),
    password: new FormControl<string>('', [Validators.required, Validators.minLength(6), Validators.maxLength(16)]),
  });

  public login(): void {
    authenticate(`${this.form.controls.username.value}|${this.form.controls.password.value}`);
  }

  public openForgotPassword(): void {
    openLinkInBrowser('https://xoaim.com/forgot-password');
  }
}
