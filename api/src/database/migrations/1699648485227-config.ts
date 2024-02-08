import { MigrationInterface, QueryRunner } from "typeorm";

export class Config1699648485227 implements MigrationInterface {
    name = 'Config1699648485227'

    public async up(queryRunner: QueryRunner): Promise<void> {
        await queryRunner.query(`CREATE TABLE \`product_configs\` (\`id\` int NOT NULL AUTO_INCREMENT, \`user_id\` int NOT NULL, \`name\` varchar(255) NOT NULL, \`created_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6), \`updated_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) ON UPDATE CURRENT_TIMESTAMP(6), \`deleted_at\` datetime(6) NULL, PRIMARY KEY (\`id\`)) ENGINE=InnoDB`);
        await queryRunner.query(`CREATE TABLE \`weapon_groups\` (\`id\` int NOT NULL AUTO_INCREMENT, \`user_id\` int NOT NULL, \`config_id\` int NOT NULL, \`name\` varchar(255) NOT NULL, \`weapons\` json NOT NULL, \`config\` json NOT NULL, \`created_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6), \`updated_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) ON UPDATE CURRENT_TIMESTAMP(6), \`deleted_at\` datetime(6) NULL, PRIMARY KEY (\`id\`)) ENGINE=InnoDB`);
    }

    public async down(queryRunner: QueryRunner): Promise<void> {
        await queryRunner.query(`DROP TABLE \`weapon_groups\``);
        await queryRunner.query(`DROP TABLE \`product_configs\``);
    }

}
