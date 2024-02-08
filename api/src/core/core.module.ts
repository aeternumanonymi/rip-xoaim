import { DynamicModule, Module, ModuleMetadata } from '@nestjs/common';
import { APP_INTERCEPTOR } from '@nestjs/core';

import { ApiConfigModule } from './api-config/api-config.module';
import { AuthModule } from './auth/auth.module';
import { ExceptionInterceptor } from './common/interceptors';
import { HealthModule } from './health/health.module';

type CoreModuleOptions = Pick<ModuleMetadata, 'imports'>;

@Module({})
export class CoreModule {
  static forRoot(options: CoreModuleOptions): DynamicModule {
    return {
      module: CoreModule,
      imports: [ApiConfigModule, AuthModule.forRoot({ imports: options.imports }), HealthModule],
      providers: [
        {
          provide: APP_INTERCEPTOR,
          useClass: ExceptionInterceptor,
        },
      ],
      exports: [ApiConfigModule],
    };
  }
}
