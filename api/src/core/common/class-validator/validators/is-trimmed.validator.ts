import { Matches, ValidationOptions } from 'class-validator';

export const IsTrimmed = (validationOpts?: ValidationOptions): PropertyDecorator =>
  Matches(/^$|^[^\s]$|^[^\s].*[^\s]$/s, {
    message: (validationArgs) => `${validationArgs.property} must be trimmed`,
    ...validationOpts,
  });
