import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouterModule, Routes } from '@angular/router';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { SwiperModule } from 'swiper/angular';

import { AppComponent } from './app.component';
import { LayoutModule } from './layout/layout.module';
import { ApiModule } from '@api/api.module';
import { NotFoundComponent, ForbiddenComponent } from './error-pages';
import { HTTP_INTERCEPTORS } from '@angular/common/http';
import { DecryptionInterceptor } from '@shared/interceptors';
import { LoginDialogComponent, ConfigDialogComponent, ConfigWeaponGroupDialogComponent, KeySelectionDialogComponent } from './dialogs';
import { SharedModule } from '@shared/shared.module';

import {
  ApplyComponent,
  ConfigsComponent,
  DashboardComponent,
  DiscordComponent,
  DocumentationGeneralComponent,
  DocumentationAimbotComponent,
  DocumentationTriggerbotComponent,
  DocumentationUtilityComponent,
  DocumentationIdlerComponent,
  FAQComponent,
  HomeComponent,
  RadarComponent,
  IdlerComponent,
  SettingsComponent,
  SubscriptionComponent,
  DocumentationSubscriptionComponent,
  DownloadComponent,
} from './pages';

import {
  HomeBannerComponent,
  HomeAboutComponent,
  HomeFeaturesComponent,
  HomePaymentsComponent,
  CustomerLayoutComponent,
  DocumentationLayoutComponent,
  CustomerConfigsGeneralComponent,
  CustomerConfigsAimbotComponent,
  CustomerConfigsTriggerbotComponent,
  CustomerConfigsUtilityComponent,
  CustomerConfigsRulesComponent,
  CustomerConfigsSoundESPComponent,
  ConfigKeySelectorComponent,
  ConfigSliderInputComponent,
  ConfigSwitchComponent,
} from './components';
import { AuthGuard } from '@shared/guards';

const routes: Routes = [
  // Public pages
  { path: '', component: HomeComponent, pathMatch: 'full' },
  { path: 'faq', component: FAQComponent },
  { path: 'apply', component: ApplyComponent },
  { path: 'discord', component: DiscordComponent },

  // Documentation pages
  { path: 'documentation', component: DocumentationGeneralComponent },
  { path: 'documentation/aimbot', component: DocumentationAimbotComponent },
  { path: 'documentation/subscription', component: DocumentationSubscriptionComponent },
  { path: 'documentation/triggerbot', component: DocumentationTriggerbotComponent },
  { path: 'documentation/utility', component: DocumentationUtilityComponent },
  { path: 'documentation/idler', component: DocumentationIdlerComponent },

  // Customer pages
  { path: 'cpanel', component: DashboardComponent, canActivate: [AuthGuard] },
  { path: 'cpanel/configs', component: ConfigsComponent, canActivate: [AuthGuard] },
  { path: 'cpanel/radar', component: RadarComponent, canActivate: [AuthGuard] },
  { path: 'cpanel/idler', component: IdlerComponent, canActivate: [AuthGuard] },
  { path: 'cpanel/subscription', component: SubscriptionComponent, canActivate: [AuthGuard] },
  { path: 'cpanel/download', component: DownloadComponent, canActivate: [AuthGuard] },
  { path: 'cpanel/settings', component: SettingsComponent, canActivate: [AuthGuard] },

  // Error pages
  { path: '404', component: NotFoundComponent },
  { path: '403', component: ForbiddenComponent },
  { path: '**', redirectTo: '/404' },
];

// Modules
const modules = [BrowserAnimationsModule, SharedModule, LayoutModule, ApiModule];

/// Public pages
const publicPages = [HomeComponent, FAQComponent, ApplyComponent, DiscordComponent];

// Documentation pages
const documentationPages = [
  DocumentationGeneralComponent,
  DocumentationSubscriptionComponent,
  DocumentationAimbotComponent,
  DocumentationTriggerbotComponent,
  DocumentationUtilityComponent,
  DocumentationIdlerComponent,
];

// Customer pages
const customerPages = [
  DashboardComponent,
  ConfigsComponent,
  RadarComponent,
  IdlerComponent,
  SubscriptionComponent,
  DownloadComponent,
  SettingsComponent,
];

// Home components
const homeComponents = [HomeBannerComponent, HomeAboutComponent, HomeFeaturesComponent, HomePaymentsComponent];

/// Documentation components
const documentationComponents = [DocumentationLayoutComponent];

// Customer panel components
const customerComponents = [
  CustomerLayoutComponent,
  CustomerConfigsGeneralComponent,
  CustomerConfigsAimbotComponent,
  CustomerConfigsTriggerbotComponent,
  CustomerConfigsSoundESPComponent,
  CustomerConfigsUtilityComponent,
  CustomerConfigsRulesComponent,
];

// Dialogs
const dialogs = [LoginDialogComponent, KeySelectionDialogComponent, ConfigDialogComponent, ConfigWeaponGroupDialogComponent];

// Config options
const configOptions = [ConfigKeySelectorComponent, ConfigSliderInputComponent, ConfigSwitchComponent];

// All components
const allComponents = [
  ...publicPages,
  ...documentationPages,
  ...customerPages,
  ...homeComponents,
  ...documentationComponents,
  ...customerComponents,
  ...dialogs,
  ...configOptions,
];

@NgModule({
  declarations: [AppComponent, ...allComponents],
  imports: [
    BrowserModule.withServerTransition({ appId: 'serverApp' }),
    RouterModule.forRoot(routes, {
      scrollPositionRestoration: 'disabled',
      initialNavigation: 'enabledBlocking',
    }),
    ...modules,
    SwiperModule,
  ],
  providers: [
    {
      provide: HTTP_INTERCEPTORS,
      useClass: DecryptionInterceptor,
      multi: true,
    },
  ],
  bootstrap: [AppComponent],
})
export class AppModule {}
