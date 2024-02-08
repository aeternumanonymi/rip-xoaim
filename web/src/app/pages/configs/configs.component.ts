import { Dialog } from '@angular/cdk/dialog';
import { Component, Input, OnDestroy, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Subscription, take } from 'rxjs';

import { ConfigDialogComponent } from '../../dialogs/config-dialog/config-dialog.component';
import { ConfigWeaponGroupDialogComponent } from 'src/app/dialogs/weapon-group-dialog/weapon-group-dialog.component';
import { ConfirmationService, NotificationService } from '@shared/services';
import { ProductConfigService } from '@api/services';

@Component({
  selector: 'xo-configs',
  templateUrl: './configs.component.html',
  styleUrls: ['./configs.component.scss'],
})
export class ConfigsComponent implements OnInit, OnDestroy {
  public configs: any[] = [];
  public weaponGroups: any[] = [];

  public currentTab: string = 'general';

  public selectedConfigValue: any = false;
  public selectedConfig: any = false;

  public selectedWeaponGroupValue: any = false;
  public selectedWeaponGroup: any = false;

  public configTabs: any[] = [
    { value: 'general', name: 'General' },
    { value: 'aimbot', name: 'Aimbot' },
    { value: 'triggerbot', name: 'Triggerbot' },
    { value: 'sound-esp', name: 'Sound ESP' },
    { value: 'utility', name: 'Utility' },
  ];

  private subscriptions: Subscription[] = [];

  constructor(
    private readonly router: Router,
    private readonly activatedRoute: ActivatedRoute,
    private readonly dialog: Dialog,
    private readonly confirmationService: ConfirmationService,
    private readonly notificationService: NotificationService,
    private readonly productConfigService: ProductConfigService,
  ) {}

  public async ngOnInit(): Promise<void> {
    await this.getConfigs();
    await this.getGroups();

    this.activatedRoute.queryParamMap.subscribe((queryParamMap) => {
      this.currentTab = queryParamMap.get('tab') || 'general';
    });
  }

  public ngOnDestroy(): void {
    this.subscriptions.forEach((subscription) => {
      subscription.unsubscribe();
    });
  }

  public selectTab(tab: string): void {
    this.router.navigate(['/cpanel/configs'], { queryParams: { tab } });
  }

  public async onSelectConfig(): Promise<void> {
    this.selectedConfig = this.configs.find((c) => c.id === this.selectedConfigValue);
    await this.getGroups();

    if (this.weaponGroups.length) {
      this.selectedWeaponGroup = this.weaponGroups[0];
      this.selectedWeaponGroupValue = this.weaponGroups[0].id;
    }
  }

  public onSelectWeaponGroup(): void {
    this.selectedWeaponGroup = this.weaponGroups.find((g) => g.id === this.selectedWeaponGroupValue);
  }

  // -------------------- CONFIG -------------------- //
  private async getConfigs(): Promise<void> {
    const data = await this.productConfigService.getConfigs();
    this.configs = data;
    this.selectedConfig = this.configs.length ? this.configs[0] : false;
    this.selectedConfigValue = this.configs.length ? this.configs[0].id : false;
  }

  public openCreateConfigDialog(): void {
    const dialogRef = this.dialog.open(ConfigDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      data: {
        type: 'create',
        config: this.configs,
      },
    });

    dialogRef.closed.pipe(take(1)).subscribe((config: any) => {
      if (config) {
        this.configs.push(config);
        this.selectedConfig = config;
        this.selectedConfigValue = config.id;
      }
    });
  }

  public openEditConfigDialog(): void {
    const dialogRef = this.dialog.open(ConfigDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      data: {
        type: 'update',
        config: this.selectedConfig,
      },
    });

    dialogRef.closed.pipe(take(1)).subscribe((config: any) => {
      if (config) {
        const index = this.configs.indexOf(this.selectedConfig);
        this.configs[index] = config;
        this.selectedConfig.name = config.name;
        this.selectedConfigValue = '';

        setTimeout(() => {
          this.selectedConfigValue = config.id;
        });
      }
    });
  }

  public openDeleteConfigDialog(): void {
    const ref = this.confirmationService.show('Are you sure you wish to delete this config?', 'Confirm', 'Cancel');
    ref.closed.pipe(take(1)).subscribe(async (confirmation) => {
      if (confirmation) {
        await this.productConfigService.deleteConfig(this.selectedConfig.id);
        this.configs = this.configs.filter((c) => c.id !== this.selectedConfig.id);
        this.weaponGroups = [];
        this.selectedWeaponGroup = false;
        this.selectedWeaponGroupValue = false;
        this.selectedConfig = false;
        this.selectedConfigValue = false;

        if (this.configs.length) {
          this.selectedConfig = this.configs[0];
          this.selectedConfigValue = this.configs[0].id;
          await this.getGroups();
        }
      }
    });
  }

  // -------------------- WEAPON GROUP -------------------- //

  private async getGroups(): Promise<void> {
    if (this.selectedConfig && this.selectedConfigValue) {
      const data = await this.productConfigService.getWeaponGroups(this.selectedConfig.id);
      this.weaponGroups = data;

      for (const group of this.weaponGroups) {
        group.config = JSON.parse(group.config);
      }

      this.selectedWeaponGroup = this.weaponGroups.length ? this.weaponGroups[0] : false;
      this.selectedWeaponGroupValue = this.weaponGroups.length ? this.weaponGroups[0].id : false;
    }
  }

  public openCreateWeaponGroupDialog(): void {
    const dialogRef = this.dialog.open(ConfigWeaponGroupDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      data: {
        type: 'create',
        group: this.selectedWeaponGroup,
        configId: this.selectedConfig.id,
      },
    });

    dialogRef.closed.pipe(take(1)).subscribe((weaponGroup: any) => {
      if (weaponGroup) {
        this.weaponGroups.push(weaponGroup);
        this.selectedWeaponGroup = weaponGroup;
        this.selectedWeaponGroupValue = weaponGroup.id;
      }
    });
  }

  public openEditWeaponGroupDialog(): void {
    const dialogRef = this.dialog.open(ConfigWeaponGroupDialogComponent, {
      disableClose: true,
      closeOnNavigation: true,
      data: {
        type: 'update',
        group: this.selectedWeaponGroup,
        configId: this.selectedConfig.id,
        weaponGroupId: this.selectedWeaponGroup.id,
      },
    });

    dialogRef.closed.pipe(take(1)).subscribe((weaponGroup: any) => {
      if (weaponGroup) {
        const index = this.weaponGroups.indexOf(this.selectedWeaponGroup);
        this.weaponGroups[index] = weaponGroup;
        this.selectedWeaponGroup.name = weaponGroup.name;
        this.selectedWeaponGroup.weapons = weaponGroup.weapons;
        this.selectedWeaponGroupValue = '';

        setTimeout(() => {
          this.selectedWeaponGroupValue = weaponGroup.id;
        });
      }
    });
  }

  public openDeleteWeaponGroupDialog(): void {
    const ref = this.confirmationService.show('Are you sure you wish to delete this weapon group?', 'Confirm', 'Cancel');
    ref.closed.pipe(take(1)).subscribe(async (confirmation) => {
      if (confirmation) {
        await this.productConfigService.deleteWeaponGroup(this.selectedConfig.id, this.selectedWeaponGroup.id);
        this.weaponGroups = this.weaponGroups.filter((g) => g.id !== this.selectedWeaponGroupValue);
        this.selectedWeaponGroup = this.weaponGroups.length ? this.weaponGroups[0] : false;
        this.selectedWeaponGroupValue = this.weaponGroups.length ? this.weaponGroups[0].id : false;
      }
    });
  }

  public updateConfigProperty(tab: string, config: any): void {
    if (!this.selectedWeaponGroup?.config) {
      this.selectedWeaponGroup.config = {};
    }

    this.selectedWeaponGroup.config[tab] = config;
  }

  public async saveConfig(): Promise<void> {
    const payload = {
      name: this.selectedWeaponGroup.name,
      weapons: this.selectedWeaponGroup.weapons,
      config: JSON.stringify(this.selectedWeaponGroup.config),
    };

    await this.productConfigService.updateWeaponGroup(this.selectedConfig.id, this.selectedWeaponGroup.id, payload);
    this.notificationService.show('Your config has been successfully saved!');
  }
}
