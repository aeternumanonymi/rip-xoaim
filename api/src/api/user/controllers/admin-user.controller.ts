import { Body, Controller, Delete, Get, Param, Post, Put, Query, Req, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiOkResponse, ApiTags } from '@nestjs/swagger';

import { JwtAuthGuard } from '../../../core/auth/guards';
import { AuthenticatedRequest } from '../../../core/auth/interfaces';
import { ApiCreatedDataResponse, ApiOkDataResponse, ApiOkDataWithMetaResponse } from '../../../core/common/decorators';
import { DataResponseDto, DataWithMetaResponseDto } from '../../../core/common/dtos';
import {
  AdminChangeUserPasswordBodyDto,
  AdminCreateUserBodyDto,
  AdminListUserMetaDto,
  AdminListUserQueryDto,
  AdminUpdateUserBodyDto,
  AdminUserDto,
} from '../dtos';
import { UserService } from '../services';

@Controller('/admin/users')
@UseGuards(JwtAuthGuard)
@ApiBearerAuth()
@ApiTags('user')
export class AdminUserController {
  constructor(private readonly userService: UserService) {}

  @Get('/')
  @ApiOkDataWithMetaResponse({
    data: { type: AdminUserDto, isArray: true },
    meta: { type: AdminListUserMetaDto },
  })
  async list(@Query() query: AdminListUserQueryDto): Promise<DataWithMetaResponseDto<AdminUserDto[], AdminListUserMetaDto>> {
    const { users, count } = await this.userService.listUsers(query, query.limit, query.offset, query.sort, query.direction, AdminUserDto);
    return { data: users, meta: { count } };
  }

  @Post('/')
  @ApiCreatedDataResponse({ data: { type: AdminUserDto } })
  async post(@Body() data: AdminCreateUserBodyDto): Promise<DataResponseDto<AdminUserDto>> {
    return { data: await this.userService.createUser(data, AdminUserDto) };
  }

  @Get('/:id')
  @ApiOkDataResponse({ data: { type: AdminUserDto } })
  async get(@Param('id') id: number): Promise<DataResponseDto<AdminUserDto>> {
    return { data: await this.userService.getUser(id, AdminUserDto) };
  }

  @Put('/:id')
  @ApiOkDataResponse({ data: { type: AdminUserDto } })
  async put(@Param('id') id: number, @Body() data: AdminUpdateUserBodyDto, @Req() request: AuthenticatedRequest): Promise<DataResponseDto<AdminUserDto>> {
    return { data: await this.userService.updateUser(id, request.user, data) };
  }

  @Put('/:id/password')
  @ApiOkResponse()
  changePassword(@Param('id') id: number, @Body() data: AdminChangeUserPasswordBodyDto): Promise<void> {
    return this.userService.changeUserPassword(id, data);
  }

  @Post('/:id/resend-email-verification-email')
  @ApiOkResponse()
  resendEmailVerificationEmail(@Param('id') id: number): Promise<void> {
    return this.userService.resendEmailVerificationEmailToUser(id);
  }

  @Delete('/:id')
  @ApiOkResponse()
  async delete(@Param('id') id: number): Promise<void> {
    await this.userService.deleteUser(id);
  }
}
