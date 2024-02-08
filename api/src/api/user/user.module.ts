import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';

import { ApiConfigModule } from '../../core/api-config/api-config.module';
import { AUTH_USER_SERVICE_TOKEN } from '../../core/auth/auth.constants';
import { AdminUserController, AppUserController } from './controllers';
import { UserEmailVerificationEntity, UserEntity, UserPasswordRecoveryEntity } from './entities';
import { UserService } from './services';

@Module({
  imports: [ApiConfigModule, TypeOrmModule.forFeature([UserEmailVerificationEntity, UserEntity, UserPasswordRecoveryEntity])],
  controllers: [AppUserController, AdminUserController],
  providers: [
    {
      provide: AUTH_USER_SERVICE_TOKEN,
      useExisting: UserService,
    },
    UserService,
  ],
  exports: [AUTH_USER_SERVICE_TOKEN, UserService],
})
export class UserModule {}
