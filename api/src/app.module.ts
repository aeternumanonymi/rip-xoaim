import { Module, ValidationPipe, NestModule, MiddlewareConsumer } from '@nestjs/common';
import { APP_PIPE } from '@nestjs/core';

import { CoreModule } from './core/core.module';
import { ApiModule } from './api/api.module';
import { AppController } from './app.controller';
import { EncryptionMiddleware } from './core/common/middlewares';

@Module({
  imports: [CoreModule.forRoot({ imports: [ApiModule] }), ApiModule],
  controllers: [AppController],
  providers: [
    {
      provide: APP_PIPE,
      useValue: new ValidationPipe({ transform: true, whitelist: true }),
    },
  ],
})
export class AppModule implements NestModule {
  configure(consumer: MiddlewareConsumer) {
    consumer.apply(EncryptionMiddleware).forRoutes('*');
  }
}
