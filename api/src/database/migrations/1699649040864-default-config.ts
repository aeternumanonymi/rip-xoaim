import { MigrationInterface, QueryRunner } from "typeorm";

export class DefaultConfig1699649040864 implements MigrationInterface {
    name = 'DefaultConfig1699649040864'

    public async up(queryRunner: QueryRunner): Promise<void> {
        await queryRunner.query(`ALTER TABLE \`product_configs\` ADD \`default\` tinyint NOT NULL`);
    }

    public async down(queryRunner: QueryRunner): Promise<void> {
        await queryRunner.query(`ALTER TABLE \`product_configs\` DROP COLUMN \`default\``);
    }

}
