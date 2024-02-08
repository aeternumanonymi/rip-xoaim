import { ErrorUtil } from '../utils';

export class NotFoundException<T extends Record<string, any>> extends Error {
  constructor(name: string, args: { readonly [key in keyof Partial<T>]: T[key] }) {
    super(ErrorUtil.buildNotFoundErrorMessage({ name, args }));
  }
}
