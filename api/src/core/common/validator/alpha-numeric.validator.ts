import { ValidatorConstraint, ValidatorConstraintInterface, ValidationArguments, ValidationOptions, registerDecorator } from 'class-validator';

@ValidatorConstraint({ name: 'alphaNumeric', async: false })
export class AlphaNumericValidator implements ValidatorConstraintInterface {
  validate(value: any, args: ValidationArguments): boolean {
    const alphanumericRegex = /^[a-zA-Z0-9-]+$/;
    if (typeof value !== 'string') {
      return false;
    }
    return alphanumericRegex.test(value);
  }

  defaultMessage(args: ValidationArguments): string {
    return 'The $property must contain only numbers and letters.';
  }
}

export function IsAlphaNumeric(validationOptions?: ValidationOptions) {
  return function (object: Object, propertyName: string) {
    registerDecorator({
      name: 'isAlphaNumeric',
      target: object.constructor,
      propertyName: propertyName,
      constraints: [],
      options: validationOptions,
      validator: AlphaNumericValidator,
    });
  };
}
