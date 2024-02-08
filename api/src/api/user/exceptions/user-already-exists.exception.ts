import { AlreadyExistsException } from '../../../core/common/exceptions';
import { UserEntity } from '../entities';

export class UserAlreadyExistsException extends AlreadyExistsException<UserEntity> {
  constructor(args: {
    readonly [key in keyof Partial<UserEntity>]: UserEntity[key];
  }) {
    super('user', args);
  }
}
