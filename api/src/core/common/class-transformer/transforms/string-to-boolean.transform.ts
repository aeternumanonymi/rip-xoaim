import { Transform, TransformOptions } from 'class-transformer';

export const TransformStringToBoolean = (tranformOpts?: TransformOptions): PropertyDecorator =>
  Transform((args) => {
    const value = typeof args.value === 'string' ? args.value.toLowerCase() : args.value;
    return ['false', 'true'].includes(value) ? value === 'true' : value;
  }, tranformOpts);
