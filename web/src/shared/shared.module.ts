import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule } from '@angular/router';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { OverlayModule } from '@angular/cdk/overlay';
import { DialogModule } from '@angular/cdk/dialog';
import { CdkTableModule } from '@angular/cdk/table';
import { MatPaginatorModule } from '@angular/material/paginator';

import {
  DropdownComponent,
  SelectComponent,
  NotificationComponent,
  ToggleSwitchComponent,
  TooltipComponent,
  TableSorterComponent,
  CheckboxComponent,
  RadioButtonComponent,
  RangeComponent,
  SliderComponent,
  IconComponent,
} from './components';

import {
  ClickOutsideDirective,
  DropdownTriggerForDirective,
  RequiredRoleDirective,
  TooltipDirective,
  AutofocusDirective,
} from './directives';

import { FirstKeyPipe, CountryPipe, SafeUrlPipe, DivideArrayPipe } from './pipes';
import { SwiperModule } from 'swiper/angular';

const modules = [
  CommonModule,
  RouterModule,
  FormsModule,
  ReactiveFormsModule,
  OverlayModule,
  DialogModule,
  CdkTableModule,
  MatPaginatorModule,
  SwiperModule,
];

const components = [
  DropdownComponent,
  SelectComponent,
  NotificationComponent,
  ToggleSwitchComponent,
  TooltipComponent,
  TableSorterComponent,
  CheckboxComponent,
  RadioButtonComponent,
  RangeComponent,
  SliderComponent,
  IconComponent,
];

const directives = [ClickOutsideDirective, DropdownTriggerForDirective, RequiredRoleDirective, TooltipDirective, AutofocusDirective];

const pipes = [FirstKeyPipe, CountryPipe, SafeUrlPipe, DivideArrayPipe];

@NgModule({
  imports: [...modules],
  declarations: [...components, ...pipes, ...directives],
  exports: [...modules, ...components, ...pipes, ...directives],
})
export class SharedModule {}
