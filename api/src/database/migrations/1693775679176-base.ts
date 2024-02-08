import { MigrationInterface, QueryRunner } from "typeorm";

export class Base1693775679176 implements MigrationInterface {
    name = 'Base1693775679176'

    public async up(queryRunner: QueryRunner): Promise<void> {
        await queryRunner.query(`CREATE TABLE \`user_password_recovery\` (\`id\` int NOT NULL AUTO_INCREMENT, \`user_id\` int NOT NULL, \`code\` varchar(255) NOT NULL, \`created_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6), \`expires_at\` datetime NOT NULL, \`completed_at\` timestamp NULL, PRIMARY KEY (\`id\`)) ENGINE=InnoDB`);
        await queryRunner.query(`CREATE TABLE \`users\` (\`id\` int NOT NULL AUTO_INCREMENT, \`role\` varchar(255) NOT NULL, \`username\` varchar(255) NOT NULL, \`email\` varchar(255) NOT NULL, \`email_verified\` tinyint NOT NULL DEFAULT 0, \`password_hash\` varchar(255) NOT NULL, \`created_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6), \`updated_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) ON UPDATE CURRENT_TIMESTAMP(6), \`deleted_at\` datetime(6) NULL, PRIMARY KEY (\`id\`)) ENGINE=InnoDB`);
        await queryRunner.query(`CREATE TABLE \`email_verification\` (\`id\` int NOT NULL AUTO_INCREMENT, \`user_id\` int NOT NULL, \`code\` varchar(36) NOT NULL, \`created_at\` datetime(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6), \`expires_at\` datetime NOT NULL, \`verified_at\` timestamp NULL, PRIMARY KEY (\`id\`)) ENGINE=InnoDB`);
        await queryRunner.query(`ALTER TABLE \`user_password_recovery\` ADD CONSTRAINT \`FK_4f365d82e1c6708dd643ddd1155\` FOREIGN KEY (\`user_id\`) REFERENCES \`users\`(\`id\`) ON DELETE NO ACTION ON UPDATE NO ACTION`);
        await queryRunner.query(`ALTER TABLE \`email_verification\` ADD CONSTRAINT \`FK_e7eb5e3c3dd984d69f6eb1cdf1c\` FOREIGN KEY (\`user_id\`) REFERENCES \`users\`(\`id\`) ON DELETE NO ACTION ON UPDATE NO ACTION`);
    }

    public async down(queryRunner: QueryRunner): Promise<void> {
        await queryRunner.query(`ALTER TABLE \`email_verification\` DROP FOREIGN KEY \`FK_e7eb5e3c3dd984d69f6eb1cdf1c\``);
        await queryRunner.query(`ALTER TABLE \`user_password_recovery\` DROP FOREIGN KEY \`FK_4f365d82e1c6708dd643ddd1155\``);
        await queryRunner.query(`DROP TABLE \`email_verification\``);
        await queryRunner.query(`DROP TABLE \`users\``);
        await queryRunner.query(`DROP TABLE \`user_password_recovery\``);
    }

}
