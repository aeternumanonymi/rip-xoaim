import { Module } from '@nestjs/common';

import { ApiConfigModule } from '../../core/api-config/api-config.module';
import { ProductConfigService } from './services';
import { AdminProductConfigController, AppProductConfigController } from './controllers';
import { TypeOrmModule } from '@nestjs/typeorm';
import { ProductConfigEntity, WeaponGroupEntity } from './entities';

@Module({
  imports: [ApiConfigModule, TypeOrmModule.forFeature([ProductConfigEntity, WeaponGroupEntity])],
  providers: [ProductConfigService],
  controllers: [AdminProductConfigController, AppProductConfigController],
  exports: [ProductConfigService],
})
export class ProductConfigModule {}
