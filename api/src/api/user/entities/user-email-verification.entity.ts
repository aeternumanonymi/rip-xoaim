import { Column, CreateDateColumn, Entity, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';

import { UserEntity } from './user.entity';

@Entity({ name: 'email_verification' })
export class UserEmailVerificationEntity {
  @PrimaryGeneratedColumn()
  id!: number;

  @Column()
  userId!: number;

  @ManyToOne(() => UserEntity, (user) => user.emailVerifications)
  user?: UserEntity;

  @Column({ generated: 'uuid' })
  code!: string;

  @CreateDateColumn()
  createdAt!: Date;

  @Column()
  expiresAt!: Date;

  @Column({ type: 'timestamp', default: null })
  verifiedAt!: Date | null;
}
