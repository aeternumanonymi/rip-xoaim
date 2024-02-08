import { Pipe, PipeTransform } from '@angular/core';
import { DomSanitizer, SafeResourceUrl } from '@angular/platform-browser';

@Pipe({
  name: 'safeUrl',
})
export class SafeUrlPipe implements PipeTransform {
  constructor(private readonly sanitizer: DomSanitizer) {}
  transform(url: string): SafeResourceUrl {
    if (url) return this.sanitizer.bypassSecurityTrustResourceUrl(url);
    return '';
  }
}