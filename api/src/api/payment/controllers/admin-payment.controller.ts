import { Controller, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiTags } from '@nestjs/swagger';

import { JwtAuthGuard } from '../../../core/auth/guards';
import { PaymentService } from '../services';

@Controller('/admin/payment')
@UseGuards(JwtAuthGuard)
@ApiBearerAuth()
@ApiTags('payment')
export class AdminPaymentController {
  constructor(private readonly paymentService: PaymentService) {}
}
