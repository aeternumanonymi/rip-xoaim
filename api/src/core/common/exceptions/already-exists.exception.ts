import { ErrorUtil } from '../utils';
import { ConflictException } from './conflict.exception';

export class AlreadyExistsException<T extends Record<string, any>> extends ConflictException {
  constructor(name: string, args: { readonly [key in keyof Partial<T>]: T[key] }) {
    super(ErrorUtil.buildAlreadyExistsErrorMessage({ name, args }));
  }
}
