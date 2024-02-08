import { Injectable } from '@angular/core';
import { DataResponse } from '../interfaces';
import { ApiService } from './api.service';

@Injectable({
  providedIn: 'root',
})
export class ProductConfigService {
  constructor(private readonly apiService: ApiService) {}

  public async createConfig(payload: any): Promise<any> {
    const { data } = await this.apiService.post<DataResponse<any>>('/app/product-config', payload);
    return data;
  }

  public async getConfigs(): Promise<any> {
    const { data } = await this.apiService.get<DataResponse<any>>('/app/product-config');
    return data;
  }

  public async getConfigById(id: number): Promise<any> {
    const { data } = await this.apiService.get<DataResponse<any>>(`/app/product-config/${id}`);
    return data;
  }

  public async updateConfig(id: number, payload: any): Promise<any> {
    const { data } = await this.apiService.put<DataResponse<any>>(`/app/product-config/${id}`, payload);
    return data;
  }

  public async deleteConfig(id: number): Promise<any> {
    return await this.apiService.delete(`/app/product-config/${id}`);
  }

  public async createWeaponGroup(configId: number, payload: any): Promise<any> {
    const { data } = await this.apiService.post<DataResponse<any>>(`/app/product-config/${configId}/weapon-group`, payload);
    return data;
  }

  public async updateWeaponGroup(configId: number, groupId: number, payload: any): Promise<any> {
    const { data } = await this.apiService.put<DataResponse<any>>(`/app/product-config/${configId}/weapon-group/${groupId}`, payload);
    return data;
  }

  public async deleteWeaponGroup(configId: number, groupId: number): Promise<void> {
    return await this.apiService.delete(`/app/product-config/${configId}/weapon-group/${groupId}`);
  }

  public async getWeaponGroups(configId: number): Promise<any> {
    const { data } = await this.apiService.get<DataResponse<any>>(`/app/product-config/${configId}/weapon-group`);
    return data;
  }

  public async getWeaponGroupById(configId: number, groupId: number): Promise<any> {
    const { data } = await this.apiService.get<DataResponse<any>>(`/app/product-config/${configId}/weapon-group/${groupId}`);
    return data;
  }
}
