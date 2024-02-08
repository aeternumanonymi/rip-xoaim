import { Component, OnInit, NgZone } from '@angular/core';

@Component({
  selector: 'app-loading',
  templateUrl: './loading.component.html',
  styleUrls: ['./loading.component.scss'],
})
export class LoadingComponent implements OnInit {
  public loadingText: string = '';

  private symbols: string[] = [
    '!',
    '"',
    '#',
    '¤',
    '$',
    '%',
    '&',
    '/',
    '(',
    ')',
    '=',
    '?',
    '+',
    '*',
    '-',
    ':',
    ';',
    '_',
    '<',
    '>',
    '|',
    '^',
    '~',
    '`',
  ];

  constructor(private readonly ngZone: NgZone) {}

  public ngOnInit(): void {
    (window['ngLoadingComponent' as any] as any) = {
      component: this,
      zone: this.ngZone,
      _setLoadingStatus: (status: string) => this.setLoadingStatus(status),
    };
  }

  private setLoadingStatus(status: string): void {
    this.loadingText = '';
    this.decryptText(status);
  }

  private decryptText(
    value: string,
    partial: string = '',
    charPosition: number = 0,
    symbolPosition: number = 0
  ): void {
    const valueChars = [...value];

    if (symbolPosition < 3) {
      this.loadingText =
        partial + this.symbols[Math.floor(Math.random() * this.symbols.length)];
      setTimeout(() => {
        this.decryptText(value, partial, charPosition, symbolPosition + 1);
      }, 10);
    } else if (charPosition < valueChars.length) {
      partial += valueChars[charPosition];
      this.loadingText = partial;

      if (charPosition < valueChars.length - 1) {
        charPosition++;
        setTimeout(() => {
          this.decryptText(value, partial, charPosition, 0);
        }, 10);
      }
    }
  }
}
