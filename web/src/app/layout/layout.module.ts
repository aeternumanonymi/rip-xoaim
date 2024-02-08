import { NgModule } from '@angular/core';

import { HeaderComponent } from './header/header.component';
import { FooterComponent } from './footer/footer.component';
import { MobileMenuComponent } from './mobile-menu/mobile-menu.component';
import { SharedModule } from '@shared/shared.module';

const components = [HeaderComponent, FooterComponent, MobileMenuComponent];

@NgModule({
  declarations: [...components],
  imports: [SharedModule],
  exports: [...components],
})
export class LayoutModule {}
