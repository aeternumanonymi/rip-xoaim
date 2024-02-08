import { Column, CreateDateColumn, Entity, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';

import { UserEntity } from './user.entity';

@Entity({ name: 'user_password_recovery' })
export class UserPasswordRecoveryEntity {
  @PrimaryGeneratedColumn()
  id!: number;

  @Column()
  userId!: number;

  @ManyToOne(() => UserEntity, (user: UserEntity) => user.passwordRecovery)
  user!: UserEntity;

  @Column()
  code!: string;

  @CreateDateColumn()
  createdAt!: Date;

  @Column()
  expiresAt!: Date;

  @Column({ type: 'timestamp', default: null })
  completedAt!: Date | null;
}
