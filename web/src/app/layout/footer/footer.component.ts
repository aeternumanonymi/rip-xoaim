import { Component } from '@angular/core';

@Component({
  selector: 'xo-footer',
  templateUrl: './footer.component.html',
  styleUrls: ['./footer.component.scss'],
})
export class FooterComponent {
  public currentYear = new Date().getUTCFullYear();
}
