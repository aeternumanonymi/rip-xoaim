import { isPlatformBrowser } from '@angular/common';
import { Component, Inject, PLATFORM_ID } from '@angular/core';

@Component({
  selector: 'xo-discord',
  templateUrl: './discord.component.html',
  styleUrls: ['./discord.component.scss'],
})
export class DiscordComponent {
  private isBrowser: boolean = false;

  constructor(@Inject(PLATFORM_ID) platformId: Object) {
    this.isBrowser = isPlatformBrowser(platformId);
  }

  public ngOnInit(): void {
    if (this.isBrowser) {
      window.location.href = 'https://discord.gg/Jdz5n7XJ';
    }
  }
}
