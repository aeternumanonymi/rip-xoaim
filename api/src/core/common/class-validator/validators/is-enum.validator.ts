import { IsEnum as IsEnumValidator, ValidationOptions } from 'class-validator';

export const IsEnum = (enumeration: Record<string, unknown>, validationOpts?: ValidationOptions): PropertyDecorator =>
  IsEnumValidator(enumeration, {
    message: (validationArgs) => `${validationArgs.property} must be a valid enum value: ${Object.values(enumeration).join(', ')}`,
    ...validationOpts,
  });
