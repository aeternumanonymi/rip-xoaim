import { Component, Output, TemplateRef, ViewChild, EventEmitter } from '@angular/core';
import { DropdownPanel } from '@shared/interfaces';

@Component({
  selector: 'xo-dropdown',
  templateUrl: './dropdown.component.html',
  styleUrls: ['./dropdown.component.scss'],
})
export class DropdownComponent implements DropdownPanel {
  @ViewChild(TemplateRef) templateRef!: TemplateRef<any>;
  @Output() closed = new EventEmitter<void>();
}
