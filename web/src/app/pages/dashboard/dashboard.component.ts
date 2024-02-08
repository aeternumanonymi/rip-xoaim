import { Component } from '@angular/core';

@Component({
  selector: 'xo-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss'],
})
export class DashboardComponent {
  public configs: any[] = [
    { id: 1, name: 'Safe' },
    { id: 2, name: 'Legit' },
    { id: 3, name: 'Semi-legit' },
  ];
}
