import { NotFoundException } from '../../../core/common/exceptions';
import { UserEntity } from '../entities';

export class UserNotFoundException extends NotFoundException<UserEntity> {
  constructor(args: {
    readonly [key in keyof Partial<UserEntity>]: UserEntity[key];
  }) {
    super('user', args);
  }
}
