import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { SnakeNamingStrategy } from 'typeorm-naming-strategies';
import * as glob from 'glob';

import { ApiConfig, JwtConfig, TypeOrmConfig } from './interfaces';

@Injectable()
export class ApiConfigService {
  constructor(private readonly configService: ConfigService) {}

  get apiConfig(): ApiConfig {
    const corsOrigin = this.getValue<string>('API_CORS_ORIGIN');

    return {
      corsOrigin: corsOrigin.includes(',') ? corsOrigin.split(',') : corsOrigin,
      documentationEnabled: this.getValue<boolean>('API_DOCUMENTATION_ENABLED'),
      webUrl: this.getValue<string>('API_WEB_URL'),
      apiUrl: this.getValue<string>('API_URL'),
      encryptionKey: this.getValue<string>('API_ENCRYPTION_KEY'),
      port: this.getValue<number>('API_PORT'),
    };
  }

  get jwtConfig(): JwtConfig {
    return {
      accessTokenExpiresIn: this.getValue<string>('JWT_ACCESS_TOKEN_EXPIRY'),
      refreshTokenExpiresIn: this.getValue<string>('JWT_REFRESH_TOKEN_EXPIRY'),
    };
  }

  get typeOrmConfig(): TypeOrmConfig {
    return {
      type: 'mysql',
      host: this.getValue<string>('DATABASE_HOST'),
      port: this.getValue<number>('DATABASE_PORT'),
      username: this.getValue<string>('DATABASE_USERNAME'),
      password: this.getValue<string>('DATABASE_PASSWORD'),
      database: this.getValue<string>('DATABASE_NAME'),
      migrations: [...this.listClasses(`${__dirname}/../../database/migrations/*.js`)],
      namingStrategy: new SnakeNamingStrategy(),
      autoLoadEntities: true,
      migrationsRun: true,
    };
  }

  private getValue<T>(key: string): T {
    const value = this.configService.get<T>(key);
    if (value === undefined) throw new Error(`Configuration variable with key '${key}' not found.`);
    return value;
  }

  private listClasses(globPattern: string): any[] {
    // eslint-disable-next-line @typescript-eslint/no-var-requires
    return glob.sync(globPattern, { ignore: '**/*.d.ts' }).map((filePath) => Object.values(require(filePath))[0]);
  }
}
