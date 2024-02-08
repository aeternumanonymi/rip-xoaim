import { DIALOG_DATA, DialogRef } from '@angular/cdk/dialog';
import { Component, Inject, Output } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { ProductConfigService } from '@api/services';

@Component({
  selector: 'xo-weapon-group-dialog',
  templateUrl: 'weapon-group-dialog.component.html',
  styleUrls: ['./weapon-group-dialog.component.scss'],
})
export class ConfigWeaponGroupDialogComponent {
  public form = new FormGroup({
    name: new FormControl<string>('', [
      Validators.required,
      Validators.minLength(3),
      Validators.maxLength(16),
      Validators.pattern('^[a-zA-Z0-9-]+$'),
    ]),
  });

  public pistols: any[] = [
    { id: 1, name: 'USP' },
    { id: 2, name: 'Glock' },
    { id: 3, name: 'Deagle' },
    { id: 4, name: 'P228' },
    { id: 5, name: 'Elite' },
    { id: 6, name: 'Five-Seven' },
  ];

  public shotguns: any[] = [
    { id: 10, name: 'M3' },
    { id: 11, name: 'XM1014' },
  ];

  public smgs: any[] = [
    { id: 20, name: 'MP5' },
    { id: 21, name: 'TMP' },
    { id: 22, name: 'P90' },
    { id: 23, name: 'Mac 10' },
    { id: 24, name: 'UMP45' },
  ];

  public rifles: any[] = [
    { id: 30, name: 'AK-47' },
    { id: 31, name: 'SG552' },
    { id: 32, name: 'M4A1' },
    { id: 33, name: 'Aug' },
    { id: 37, name: 'SG550' },
    { id: 38, name: 'Galil' },
    { id: 39, name: 'Famas' },
  ];

  public snipers: any[] = [
    { id: 34, name: 'Scout' },
    { id: 35, name: 'AWP' },
    { id: 36, name: 'G3SG1' },
  ];

  public heavyWeapons: any[] = [{ id: 40, name: 'M249' }];

  public groups: any[] = [
    { id: 1, name: 'Pistols', weapons: this.pistols },
    { id: 2, name: 'Shotguns', weapons: this.shotguns },
    { id: 3, name: 'SMGS', weapons: this.smgs },
    { id: 4, name: 'Rifles', weapons: this.rifles },
    { id: 5, name: 'Snipers', weapons: this.snipers },
    { id: 6, name: 'Heavy weapons', weapons: this.heavyWeapons },
  ];

  public selectedWeaponIds: number[] = [];
  public selectedGroupValue: any;
  public selectedGroup: any;

  public isCreate: boolean = false;

  private configId!: number;
  private weaponGroupId!: number;

  constructor(
    @Inject(DIALOG_DATA) readonly dialogData: any,
    public readonly dialogRef: DialogRef<any>,
    private readonly productConfigService: ProductConfigService,
  ) {
    if (dialogData.type === 'update') {
      this.form.controls.name.setValue(dialogData.group.name);
      this.selectedWeaponIds = [...JSON.parse(dialogData?.group?.weapons || '[]')];

      for (const group of this.groups) {
        for (const weapon of group.weapons) {
          if (this.selectedWeaponIds.includes(weapon.id)) {
            weapon.selected = true;
          }
        }
      }
    }

    this.isCreate = dialogData.type === 'create';
    this.configId = dialogData.configId;
    this.weaponGroupId = dialogData.weaponGroupId;

    this.selectedGroupValue = this.groups[0].id;
    this.selectedGroup = this.groups[0];
  }

  public async submit(): Promise<void> {
    const payload = {
      name: this.form.controls.name.value,
      weapons: JSON.stringify(this.selectedWeaponIds),
    };

    const result = this.isCreate
      ? await this.productConfigService.createWeaponGroup(this.configId, payload)
      : await this.productConfigService.updateWeaponGroup(this.configId, this.weaponGroupId, payload);

    this.dialogRef.close(result);
  }

  public onSelectGroup(): void {
    this.selectedGroup = this.groups.find((g) => g.id === this.selectedGroupValue);
  }

  public onWeaponSelectionChange(weapon: any): void {
    if (weapon.selected) {
      this.selectWeapon(weapon.id);
    } else {
      this.unselectWeapon(weapon.id);
    }
  }

  private selectWeapon(weaponId: number): void {
    if (!this.selectedWeaponIds.includes(weaponId)) {
      this.selectedWeaponIds.push(weaponId);
    }
  }

  // Function to unselect a specific weapon
  private unselectWeapon(weaponId: number): void {
    const index = this.selectedWeaponIds.indexOf(weaponId);
    if (index !== -1) {
      this.selectedWeaponIds.splice(index, 1);
    }
  }
}
