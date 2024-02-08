import { NamingStrategyInterface } from 'typeorm';

export interface TypeOrmConfig {
  readonly type: 'mysql';
  readonly host: string;
  readonly port: number;
  readonly username: string;
  readonly password: string;
  readonly database: string;
  readonly migrations: string[];
  readonly migrationsRun: boolean;
  readonly namingStrategy: NamingStrategyInterface;
  readonly autoLoadEntities: boolean;
}
