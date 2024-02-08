import { DynamicModule, Module, ModuleMetadata } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { readFileSync } from 'fs';
import { join } from 'path';

import { AuthService } from './auth.service';
import { AuthController } from './controllers';
import { JwtStrategy, LocalStrategy } from './strategies';
import { ApiConfigModule } from '../api-config/api-config.module';

type AuthModuleOptions = Pick<ModuleMetadata, 'imports'>;

@Module({})
export class AuthModule {
  static forRoot(options: AuthModuleOptions): DynamicModule {
    return {
      module: AuthModule,
      imports: [
        ...(options.imports ?? []),
        PassportModule,
        JwtModule.register({
          signOptions: { algorithm: 'RS256' },
          privateKey: readFileSync(join(__dirname, '../../../jwt-keys/private.key')),
          publicKey: readFileSync(join(__dirname, '../../../jwt-keys/public.key')),
        }),
        ApiConfigModule,
      ],
      controllers: [AuthController],
      providers: [AuthService, JwtStrategy, LocalStrategy],
    };
  }
}
