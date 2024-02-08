import { Pipe, PipeTransform } from '@angular/core';

@Pipe({ name: 'divideArray' })
export class DivideArrayPipe implements PipeTransform {
  transform(array: any[], groupSize: number): any[] {
    const result: any[][] = [];
    for (let i = 0; i < array.length; i += groupSize) {
      result.push(array.slice(i, i + groupSize));
    }

    return result;
  }
}
