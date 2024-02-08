import { Injectable } from '@nestjs/common';
import { CreateProductConfigDto, CreateWeaponGroupDto, ProductConfigDto, UpdateProductConfigDto, UpdateWeaponGroupDto, WeaponGroupDto } from '../dtos';
import { InjectRepository } from '@nestjs/typeorm';
import { ProductConfigEntity } from '../entities/product-config.entity';
import { Repository } from 'typeorm';
import { AuthUserDto } from '../../../core/auth/dtos';
import { WeaponGroupEntity } from '../entities';

@Injectable()
export class ProductConfigService {
  constructor(
    @InjectRepository(ProductConfigEntity) private readonly productConfigRepository: Repository<ProductConfigEntity>,
    @InjectRepository(WeaponGroupEntity) private readonly weaponGroupRepository: Repository<WeaponGroupEntity>,
  ) {}

  public async createConfig(data: CreateProductConfigDto, user: AuthUserDto): Promise<ProductConfigDto> {
    const { identifiers } = await this.productConfigRepository.insert({
      ...data,
      userId: user.id,
    });

    return await this.productConfigRepository.findOne({ where: { id: identifiers[0].id } });
  }

  public async getConfigs(): Promise<ProductConfigDto[]> {
    return await this.productConfigRepository.find();
  }

  public async getConfigById(id: number): Promise<ProductConfigDto> {
    return await this.productConfigRepository.findOne({ where: { id } });
  }

  public async updateConfig(id: number, data: UpdateProductConfigDto): Promise<ProductConfigDto> {
    await this.productConfigRepository.update({ id }, data);
    return await this.productConfigRepository.findOne({ where: { id } });
  }

  public async deleteConfig(id: number): Promise<void> {
    const weaponGroups = await this.weaponGroupRepository.find({ where: { configId: id } });
    const weaponGroupIds = weaponGroups.map((weaponGroup) => weaponGroup.id);
    if (weaponGroupIds.length) {
      await this.weaponGroupRepository.softDelete(weaponGroupIds);
    }

    await this.productConfigRepository.softDelete(id);
  }

  public async createWeaponGroup(configId: number, payload: CreateWeaponGroupDto, user: AuthUserDto): Promise<WeaponGroupDto> {
    const { identifiers } = await this.weaponGroupRepository.insert({
      ...payload,
      configId,
      userId: user.id,
    });

    return await this.weaponGroupRepository.findOne({ where: { id: identifiers[0].id } });
  }

  public async getWeaponGroups(configId: number): Promise<WeaponGroupDto[]> {
    return await this.weaponGroupRepository.find({ where: { configId } });
  }

  public async getWeaponGroupById(configId: number, weaponGroupId: number): Promise<WeaponGroupDto> {
    return await this.weaponGroupRepository.findOne({ where: { configId: configId, id: weaponGroupId } });
  }

  public async updateWeaponGroup(configId: number, weaponGroupId: number, data: UpdateWeaponGroupDto): Promise<WeaponGroupDto> {
    await this.weaponGroupRepository.update({ id: weaponGroupId, configId: configId }, data);
    return await this.weaponGroupRepository.findOne({ where: { id: weaponGroupId } });
  }

  public async deleteWeaponGroup(id: number): Promise<void> {
    await this.weaponGroupRepository.softDelete(id);
  }
}
