import * as fs from 'fs';
import * as dotenv from 'dotenv';
import * as dotenvExpand from 'dotenv-expand';
import { DataSource, DataSourceOptions } from 'typeorm';
import { SeederOptions } from 'typeorm-extension/dist/seeder';
import { SnakeNamingStrategy } from 'typeorm-naming-strategies';

const environment = process.env.NODE_ENV || 'development';
const unexpandedConfig = dotenv.parse(fs.readFileSync(`config/${environment}.env`));
const config = <Record<string, string>>dotenvExpand.expand({ parsed: unexpandedConfig }).parsed;

const entityPath = 'src/api/**/entities/*.entity{.ts,.js}';
const migrationPath = 'src/database/migrations/*{.ts,.js}';

const options: DataSourceOptions & SeederOptions = {
  // DataSource
  type: 'mysql',
  host: config.DATABASE_HOST,
  port: +config.DATABASE_PORT,
  username: config.DATABASE_USERNAME,
  password: config.DATABASE_PASSWORD,
  database: config.DATABASE_NAME,
  migrations: [migrationPath],
  entities: [entityPath],
  synchronize: false,
  namingStrategy: new SnakeNamingStrategy(),
  timezone: 'utc',

  // Seeder
  seeds: ['./src/database/seeds/*{.ts,.js}'],
};

export const dataSource = new DataSource(options);
