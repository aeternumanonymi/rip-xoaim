import { ValueTransformer } from 'typeorm';

export const JsonTransformer: ValueTransformer = {
  to: (value: unknown): string => {
    return JSON.stringify(value);
  },
  from: (value: string): unknown => {
    return JSON.parse(value);
  },
};
