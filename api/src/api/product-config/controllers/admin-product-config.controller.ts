import { Controller, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiTags } from '@nestjs/swagger';

import { JwtAuthGuard } from '../../../core/auth/guards';
import { ProductConfigService } from '../services';

@Controller('/admin/product-config')
@UseGuards(JwtAuthGuard)
@ApiBearerAuth()
@ApiTags('product-config')
export class AdminProductConfigController {
  constructor(private readonly productConfigService: ProductConfigService) {}
}
