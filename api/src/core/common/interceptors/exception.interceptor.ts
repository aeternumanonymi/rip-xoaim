import {
  CallHandler,
  ExecutionContext,
  BadRequestException as HttpBadRequestException,
  ConflictException as HttpConflictException,
  ForbiddenException as HttpForbiddenException,
  NotFoundException as HttpNotFoundException,
  PayloadTooLargeException as HttpPayloadTooLargeException,
  PreconditionFailedException as HttpPreconditionFailedException,
  UnauthorizedException as HttpUnauthorizedException,
  UnsupportedMediaTypeException as HttpUnsupportedMediaTypeException,
  Injectable,
  NestInterceptor,
} from '@nestjs/common';
import { Observable, throwError } from 'rxjs';
import { catchError } from 'rxjs/operators';

import {
  BadRequestException,
  ConflictException,
  ForbiddenException,
  NotFoundException,
  PayloadTooLargeException,
  PreconditionFailedException,
  UnauthorizedException,
  UnsupportedMediaTypeException,
} from '../exceptions';

@Injectable()
export class ExceptionInterceptor implements NestInterceptor {
  intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
    return next.handle().pipe(catchError((err) => throwError(() => this.map(err))));
  }

  private map(err: any): any {
    if (err instanceof BadRequestException) return new HttpBadRequestException(err.message);
    if (err instanceof ConflictException) return new HttpConflictException(err.message);
    if (err instanceof ForbiddenException) return new HttpForbiddenException(err.message);
    if (err instanceof NotFoundException) return new HttpNotFoundException(err.message);
    if (err instanceof PayloadTooLargeException) return new HttpPayloadTooLargeException(err.message);
    if (err instanceof PreconditionFailedException) return new HttpPreconditionFailedException(err.message);
    if (err instanceof UnauthorizedException) return new HttpUnauthorizedException(err.message);
    if (err instanceof UnsupportedMediaTypeException) return new HttpUnsupportedMediaTypeException(err.message);
    return err;
  }
}
