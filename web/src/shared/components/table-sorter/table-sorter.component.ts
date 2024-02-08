import { Component, EventEmitter, Input, OnChanges, Output } from '@angular/core';

@Component({
  selector: 'xo-table-sorter',
  templateUrl: './table-sorter.component.html',
  styleUrls: ['./table-sorter.component.scss'],
})
export class TableSorterComponent implements OnChanges {
  @Input('current') public currentField: string = '';
  @Input('field') public sortByField: string = '';
  @Input('direction') public sortByDirection: string = '';
  @Output('onSort') public onSort: EventEmitter<any> = new EventEmitter<any>();

  public ngOnChanges(): void {
    if (this.currentField !== this.sortByField) {
      this.sortByDirection = '';
    }
  }

  public sort(): void {
    if (this.sortByField !== this.sortByField) {
      this.sortByDirection = '';
    }

    if (this.sortByDirection === '') {
      this.sortByDirection = 'ASC';
    } else if (this.sortByDirection === 'ASC') {
      this.sortByDirection = 'DESC';
    } else if (this.sortByDirection === 'DESC') {
      this.sortByDirection = '';
    }

    this.onSort.emit({
      field: this.sortByField,
      direction: this.sortByDirection,
    });
  }
}
