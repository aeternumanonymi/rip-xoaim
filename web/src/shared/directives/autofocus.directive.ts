import { AfterViewChecked, Directive, ElementRef } from '@angular/core';

@Directive({
  selector: '[xoAutofocus]',
})
export class AutofocusDirective implements AfterViewChecked {
  private done: boolean = false;

  constructor(private element: ElementRef<HTMLInputElement>) {}

  ngAfterViewChecked(): void {
    if (!this.done) {
      setTimeout(() => {
        this.element.nativeElement.focus();
        this.done = true;
      });
    }
  }
}
