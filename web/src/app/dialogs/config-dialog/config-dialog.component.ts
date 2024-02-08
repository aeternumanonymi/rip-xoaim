import { DIALOG_DATA, DialogRef } from '@angular/cdk/dialog';
import { Component, Inject } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { ProductConfigService } from '@api/services';

@Component({
  selector: 'xo-config-dialog',
  templateUrl: 'config-dialog.component.html',
  styleUrls: ['./config-dialog.component.scss'],
})
export class ConfigDialogComponent {
  public form = new FormGroup({
    name: new FormControl<string>('', [
      Validators.required,
      Validators.minLength(1),
      Validators.maxLength(16),
      Validators.pattern('^[a-zA-Z0-9-]+$'),
    ]),
  });

  public isCreate: boolean = true;
  public config: any = {};

  constructor(
    @Inject(DIALOG_DATA) readonly dialogData: any,
    public readonly dialogRef: DialogRef<any>,
    private readonly productConfigService: ProductConfigService,
  ) {
    this.config = dialogData.config;
    this.isCreate = dialogData.type === 'create';
    this.form.controls.name.setValue(this.config.name);
  }

  public async submit(): Promise<void> {
    const payload = { name: this.form.controls.name.value };
    const data = this.isCreate ? await this.createConfig(payload) : await this.updateConfig(payload);
    this.dialogRef.close(data);
  }

  public async createConfig(payload: any): Promise<any> {
    return await this.productConfigService.createConfig(payload);
  }

  public async updateConfig(payload: any): Promise<any> {
    return await this.productConfigService.updateConfig(this.config.id, payload);
  }
}
