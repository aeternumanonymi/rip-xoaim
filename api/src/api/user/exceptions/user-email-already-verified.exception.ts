import { ConflictException } from '../../../core/common/exceptions';

export class UserEmailAlreadyVerifiedException extends ConflictException {
  constructor() {
    super('User email already verified');
  }
}
