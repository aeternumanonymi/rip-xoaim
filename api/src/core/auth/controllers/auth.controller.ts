import { Body, Controller, Post, Put, Req, UseGuards } from '@nestjs/common';
import { ApiBody, ApiTags } from '@nestjs/swagger';

import { ApiCreatedDataResponse, ApiOkDataResponse } from '../../common/decorators';
import { DataResponseDto } from '../../common/dtos';
import { AuthService } from '../auth.service';
import { AccessAndRefreshTokensDto, AccessTokenDto, CreateAccessAndRefreshTokensRequestDto, UpdateAccessTokenRequestDto } from '../dtos';
import { LocalAuthGuard } from '../guards';
import { AuthenticatedRequest } from '../interfaces';

@Controller('auth')
@ApiTags('auth')
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  @Post()
  @UseGuards(LocalAuthGuard)
  @ApiBody({ type: CreateAccessAndRefreshTokensRequestDto })
  @ApiCreatedDataResponse({ data: { type: AccessAndRefreshTokensDto } })
  async createAccessAndRefreshTokens(@Req() request: AuthenticatedRequest): Promise<DataResponseDto<AccessAndRefreshTokensDto>> {
    return {
      data: await this.authService.createAccessAndRefreshTokens(request.user),
    };
  }

  @Put()
  @ApiOkDataResponse({ data: { type: AccessTokenDto } })
  async updateAccessToken(@Body() body: UpdateAccessTokenRequestDto): Promise<DataResponseDto<AccessTokenDto>> {
    return { data: await this.authService.updateAccessToken(body) };
  }
}
