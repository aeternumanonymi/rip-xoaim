import { Controller, Get } from '@nestjs/common';
import { ApiTags } from '@nestjs/swagger';
import { HealthCheck, HealthCheckResult, HealthCheckService, TypeOrmHealthIndicator } from '@nestjs/terminus';

@Controller('health')
@ApiTags('health')
export class HealthController {
  constructor(private readonly healthCheckService: HealthCheckService, private readonly typeOrmHealthIndicator: TypeOrmHealthIndicator) {}

  @Get('/')
  @HealthCheck()
  async healthCheck(): Promise<HealthCheckResult> {
    return this.healthCheckService.check([() => this.typeOrmHealthIndicator.pingCheck('database')]);
  }
}
