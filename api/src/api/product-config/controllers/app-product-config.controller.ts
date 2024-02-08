import { Body, Controller, Delete, Get, Param, Post, Put, UseGuards, Req } from '@nestjs/common';
import { ApiBearerAuth, ApiOkResponse, ApiTags } from '@nestjs/swagger';

import { JwtAuthGuard } from '../../../core/auth/guards';
import { ProductConfigService } from '../services';
import { ApiCreatedDataResponse, ApiOkDataResponse } from '../../../core/common/decorators';
import { CreateProductConfigDto, ProductConfigDto, UpdateProductConfigDto, UpdateWeaponGroupDto, WeaponGroupDto } from '../dtos';
import { DataResponseDto } from '../../../core/common/dtos';
import { AuthenticatedRequest } from '../../../core/auth/interfaces';

@Controller('/app/product-config')
@UseGuards(JwtAuthGuard)
@ApiBearerAuth()
@ApiTags('product-config')
export class AppProductConfigController {
  constructor(private readonly productConfigService: ProductConfigService) {}

  @Post('/')
  @ApiCreatedDataResponse({ data: { type: ProductConfigDto } })
  async post(@Body() body: CreateProductConfigDto, @Req() request: AuthenticatedRequest): Promise<DataResponseDto<ProductConfigDto>> {
    return { data: await this.productConfigService.createConfig(body, request.user) };
  }

  @Get('/')
  @ApiOkDataResponse({ data: { type: ProductConfigDto, isArray: true } })
  async getAll(): Promise<DataResponseDto<ProductConfigDto[]>> {
    return { data: await this.productConfigService.getConfigs() };
  }

  @Get('/:id')
  @ApiOkDataResponse({ data: { type: ProductConfigDto } })
  async getOne(@Param('id') id: number): Promise<DataResponseDto<ProductConfigDto>> {
    return { data: await this.productConfigService.getConfigById(id) };
  }

  @Put('/:id')
  @ApiOkDataResponse({ data: { type: ProductConfigDto } })
  async update(@Param('id') id: number, @Body() body: UpdateProductConfigDto): Promise<DataResponseDto<ProductConfigDto>> {
    return { data: await this.productConfigService.updateConfig(id, body) };
  }

  @Delete('/:id')
  @ApiOkResponse()
  async delete(@Param('id') id: number): Promise<void> {
    return this.productConfigService.deleteConfig(id);
  }

  // ---------------------

  @Post('/:id/weapon-group')
  @ApiCreatedDataResponse({ data: { type: WeaponGroupDto } })
  async createWeaponGroup(@Param('id') id: number, @Body() body: any, @Req() request: AuthenticatedRequest): Promise<DataResponseDto<WeaponGroupDto>> {
    return { data: await this.productConfigService.createWeaponGroup(id, body, request.user) };
  }

  @Get('/:id/weapon-group')
  @ApiOkDataResponse({ data: { type: WeaponGroupDto, isArray: true } })
  async getAllWeaponGroups(@Param('id') id: number): Promise<DataResponseDto<WeaponGroupDto[]>> {
    return { data: await this.productConfigService.getWeaponGroups(id) };
  }

  @Get('/:id/weapon-group/:groupId')
  @ApiOkDataResponse({ data: { type: WeaponGroupDto } })
  async getOneWeaponGroup(@Param('id') id: number, @Param('groupId') groupId: number): Promise<DataResponseDto<WeaponGroupDto>> {
    return { data: await this.productConfigService.getWeaponGroupById(id, groupId) };
  }

  @Put('/:id/weapon-group/:groupId')
  @ApiOkDataResponse({ data: { type: WeaponGroupDto } })
  async updateWeaponGroup(
    @Param('id') id: number,
    @Param('groupId') groupId: number,
    @Body() body: UpdateWeaponGroupDto,
  ): Promise<DataResponseDto<WeaponGroupDto>> {
    return { data: await this.productConfigService.updateWeaponGroup(id, groupId, body) };
  }

  @Delete('/:id/weapon-group/:groupId')
  @ApiOkResponse()
  async deleteWeaponGroup(@Param('groupId') id: number): Promise<void> {
    return await this.productConfigService.deleteWeaponGroup(id);
  }
}
