import { Seeder } from 'typeorm-extension';
import { DataSource } from 'typeorm';
import * as bcrypt from 'bcrypt';

import { UserEntity } from '../../api/user/entities';

export default class DefaultSeeder implements Seeder {
  public async run(dataSource: DataSource): Promise<any> {
    const userRepository = dataSource.getRepository(UserEntity);

    // Create admin account
    const passwordHash = await bcrypt.hash('adminadmin', 10);
    await userRepository.insert([
      {
        username: 'mozquito',
        email: 'priit@evenux.ee',
        emailVerified: true,
        role: 'admin',
        passwordHash: passwordHash,
      },
    ]);
  }
}
