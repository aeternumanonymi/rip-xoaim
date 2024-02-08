import { Component, Input } from '@angular/core';

@Component({
  selector: 'xo-icon[icon]',
  templateUrl: './icon.component.html',
  styleUrls: ['./icon.component.scss'],
})
export class IconComponent {
  @Input() icon!: string;
  @Input() color!: string;
  @Input() size: number = 16;
  @Input() offset!: number;
}
