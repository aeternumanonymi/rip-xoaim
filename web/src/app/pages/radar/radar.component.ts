import { Component } from '@angular/core';

@Component({
  selector: 'xo-radar',
  templateUrl: './radar.component.html',
  styleUrls: ['./radar.component.scss'],
})
export class RadarComponent {
  public testPositionX: number = 0;
  public testPositionY: number = 0;

  public ngOnInit(): void {
    this.runTest();
  }

  public runTest(): void {
    this.testPositionX = this.calculatePercentage(-1974, -2476, 1924);
    this.testPositionY = 100 - this.calculatePercentage(2139, -1104, 3296);
  }

  public calculatePercentage(value: number, min: number, max: number): number {
    if (min > max) {
      [min, max] = [max, min];
    }

    const totalRange = max - min;
    const position = value - min;

    return (position / totalRange) * 100;
  }
}
