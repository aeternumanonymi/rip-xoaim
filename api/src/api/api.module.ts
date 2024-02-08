import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { DataSource, DataSourceOptions } from 'typeorm';

import { ApiConfigModule } from '../core/api-config/api-config.module';
import { ApiConfigService } from '../core/api-config/api-config.service';
import { UserModule } from './user/user.module';
import { SchedulerModule } from './scheduler/scheduler.module';
import { ProductConfigModule } from './product-config/product-config.module';

@Module({
  imports: [
    TypeOrmModule.forRootAsync({
      useFactory: (configService: ApiConfigService) => configService.typeOrmConfig,
      dataSourceFactory: (options) => new DataSource(<DataSourceOptions>{ ...options }).initialize(),
      imports: [ApiConfigModule],
      inject: [ApiConfigService],
    }),
    UserModule,
    ProductConfigModule,
    SchedulerModule,
  ],
  exports: [UserModule],
})
export class ApiModule {}
