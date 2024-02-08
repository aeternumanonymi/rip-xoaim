import { Module } from '@nestjs/common';
import { ScheduleModule } from '@nestjs/schedule';

import { SchedulerService } from './services';

@Module({
  imports: [ScheduleModule.forRoot()],
  providers: [SchedulerService],
})
export class SchedulerModule {}
