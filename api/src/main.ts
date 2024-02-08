import { NestFactory } from '@nestjs/core';
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';
import * as requestIp from 'request-ip';

import { AppModule } from './app.module';
import { ApiConfigService } from './core/api-config/api-config.service';

const bootstrap = async () => {
  const app = await NestFactory.create(AppModule, { rawBody: true });
  const configService = app.get(ApiConfigService);

  app.enableCors({ origin: configService.apiConfig.corsOrigin });
  app.use(requestIp.mw());

  if (configService.apiConfig.documentationEnabled) {
    const config = new DocumentBuilder().addBearerAuth({ in: 'header', type: 'http' }).setTitle('API Documentation').setVersion('1.0.0').build();
    const document = SwaggerModule.createDocument(app, config);
    SwaggerModule.setup('documentation', app, document, {
      swaggerOptions: {
        operationsSorter: 'alpha',
        persistAuthorization: true,
        tagsSorter: 'alpha',
      },
    });
  }

  await app.listen(configService.apiConfig.port);
};
bootstrap();
