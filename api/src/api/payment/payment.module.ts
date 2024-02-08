import { Module } from '@nestjs/common';

import { ApiConfigModule } from '../../core/api-config/api-config.module';
import { PaymentService } from './services';
import { AdminPaymentController, AppPaymentController } from './controllers';

@Module({
  imports: [ApiConfigModule],
  providers: [PaymentService],
  controllers: [AdminPaymentController, AppPaymentController],
  exports: [PaymentService],
})
export class PaymentModule {}
