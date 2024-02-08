import { Injectable } from '@nestjs/common';
import { Cron } from '@nestjs/schedule';

@Injectable()
export class SchedulerService {
  constructor() {}

  @Cron('0 */1 * * * *') // Every 1 minute
  async doSomething1(): Promise<void> {
    // ...
  }

  @Cron('0 */4 * * *') // Every 4 hours
  async doSomething2(): Promise<void> {
    // ...
  }
}
