import { Pipe, PipeTransform } from '@angular/core';

import { getName } from 'country-list';

@Pipe({ name: 'country' })
export class CountryPipe implements PipeTransform {
  transform(countryCode?: string): string {
    return countryCode ? getName(countryCode) || '' : '';
  }
}
