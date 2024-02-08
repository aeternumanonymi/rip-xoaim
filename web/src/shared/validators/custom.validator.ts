import { AbstractControl, ValidationErrors, ValidatorFn } from '@angular/forms';
import validator from 'validator';

export class CustomValidators {
  static isMobilePhoneNumber(control: AbstractControl): { invalidMobilePhoneNumber: true } | null {
    return !validator.isMobilePhone(control.value, 'any', { strictMode: true }) ? { invalidMobilePhoneNumber: true } : null;
  }

  static isEmail(control: AbstractControl): { invalidEmail: true } | null {
    return !validator.isEmail(control.value) ? { invalidEmail: true } : null;
  }

  static isPositiveNumber(control: AbstractControl): { isNotPositive: true } | null {
    return control.value <= 0 ? { isNotPositive: true } : null;
  }

  static isUuid(control: AbstractControl): { invalidUuid: true } | null {
    return !validator.isUUID(control.value) ? { invalidUuid: true } : null;
  }

  static isIn(options: string[]): ValidatorFn {
    return (control: AbstractControl): { invalidValue: true } | null => {
      const value = control.value;
      const isValid = validator.isIn(value, options);
      return !isValid ? { invalidValue: true } : null;
    };
  }

  static isCreditCard(control: AbstractControl): { invalidCard: true } | null {
    if (!control.value) return null;
    return !validator.isCreditCard(control.value) ? { invalidCard: true } : null;
  }

  static isIBAN(control: AbstractControl): { invalidIBAN: true } | null {
    if (!control.value) return null;
    return !validator.isIBAN(control.value) ? { invalidIBAN: true } : null;
  }
}
