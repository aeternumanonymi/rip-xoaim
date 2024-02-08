import { Body, Controller, Get, Post, Put, Req, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiCreatedResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';

import { JwtAuthGuard } from '../../../core/auth/guards';
import { AuthenticatedRequest } from '../../../core/auth/interfaces';
import { ApiCreatedDataResponse, ApiOkDataResponse } from '../../../core/common/decorators';
import { DataResponseDto } from '../../../core/common/dtos';
import {
  AppCreateUserBodyDto,
  AppUserDto,
  AppVerifyEmailBodyDto,
  AppChangeUserPasswordBodyDto,
  AppCreateUserPasswordRecoveryBodyDto,
  AppUpdateSelfBodyDto,
} from '../dtos';
import { ResetUserPasswordBodyDto } from '../dtos/reset-user-password-body.dto';
import { UserService } from '../services';

@Controller('/app/users')
@ApiTags('user')
export class AppUserController {
  constructor(private readonly userService: UserService) {}

  @Post('/')
  @ApiCreatedDataResponse({ data: { type: AppUserDto } })
  async post(@Body() data: AppCreateUserBodyDto): Promise<DataResponseDto<AppUserDto>> {
    return { data: await this.userService.createUser(data, AppUserDto) };
  }

  @Get('/me')
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth()
  @ApiOkDataResponse({ data: { type: AppUserDto } })
  async getMe(@Req() request: AuthenticatedRequest): Promise<DataResponseDto<AppUserDto>> {
    return { data: await this.userService.getMe(request.user, AppUserDto) };
  }

  @Put('/me')
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth()
  @ApiOkResponse()
  updateSelf(@Req() request: AuthenticatedRequest, @Body() data: AppUpdateSelfBodyDto): Promise<AppUserDto> {
    return this.userService.updateSelf(request.user, data);
  }

  @Put('/me/password')
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth()
  @ApiOkResponse()
  changePassword(@Req() request: AuthenticatedRequest, @Body() data: AppChangeUserPasswordBodyDto): Promise<void> {
    return this.userService.changePassword(request.user, data);
  }

  @Post('/password-recovery')
  @ApiCreatedResponse()
  createPasswordRecovery(@Body() data: AppCreateUserPasswordRecoveryBodyDto): Promise<void> {
    return this.userService.createPasswordRecovery(data);
  }

  @Post('/password-reset')
  @ApiOkResponse()
  resetPassword(@Body() data: ResetUserPasswordBodyDto): Promise<void> {
    return this.userService.resetPassword(data);
  }

  @Post('/me/resend-email-verification-email')
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth()
  @ApiOkResponse()
  resendEmailVerificationEmail(@Req() request: AuthenticatedRequest): Promise<void> {
    return this.userService.resendEmailVerificationEmailToSelf(request.user);
  }

  @Post('/me/verify-email')
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth()
  @ApiOkResponse()
  verifyEmail(@Req() request: AuthenticatedRequest, @Body() data: AppVerifyEmailBodyDto): Promise<void> {
    return this.userService.verifyEmailAddress(request.user, data);
  }
}
