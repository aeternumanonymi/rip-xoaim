import { Controller, Get, HttpCode } from '@nestjs/common';

@Controller('/')
export class AppController {
  @Get()
  @HttpCode(200)
  getMain(): string {
    return 'XOAim API 1.0.0';
  }
}
