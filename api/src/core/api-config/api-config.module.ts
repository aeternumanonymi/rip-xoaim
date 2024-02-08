import { Module } from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';

import { ApiConfigService } from './api-config.service';
import validationSchema from './validation-schema';

@Module({
  imports: [
    ConfigModule.forRoot({
      envFilePath: `./config/${process.env.NODE_ENV}.env`,
      expandVariables: true,
      validationSchema: validationSchema,
    }),
  ],
  providers: [ApiConfigService, ConfigService],
  exports: [ApiConfigService],
})
export class ApiConfigModule {}
