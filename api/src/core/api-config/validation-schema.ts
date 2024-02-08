import * as Joi from 'joi';

const validationSchema = Joi.object({
  NODE_ENV: Joi.string().optional().valid('development', 'production'),

  API_CORS_ORIGIN: Joi.string().required(),
  API_DOCUMENTATION_ENABLED: Joi.boolean().required(),
  API_WEB_URL: Joi.string().uri().required(),
  API_URL: Joi.string().uri().required(),
  API_ENCRYPTION_KEY: Joi.string().required(),
  API_PORT: Joi.string().required(),

  DATABASE_HOST: Joi.string().required(),
  DATABASE_PORT: Joi.number().required(),
  DATABASE_USERNAME: Joi.string().required(),
  DATABASE_PASSWORD: Joi.string().required(),
  DATABASE_NAME: Joi.string().required(),

  JWT_ACCESS_TOKEN_EXPIRY: Joi.string().required(),
  JWT_REFRESH_TOKEN_EXPIRY: Joi.string().required(),
});

export default validationSchema;
