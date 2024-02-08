import { Injectable } from '@angular/core';
import { HttpInterceptor, HttpHandler, HttpRequest, HttpResponse, HttpEvent, HttpHeaderResponse } from '@angular/common/http';
import { Observable } from 'rxjs';
import { filter, map, catchError } from 'rxjs/operators';
import * as CryptoJS from 'crypto-js';
import { environment } from '@env/environment';

@Injectable()
export class DecryptionInterceptor implements HttpInterceptor {
  intercept(request: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
    return next.handle(request).pipe(
      filter((event: HttpEvent<any>) => event instanceof HttpResponse || event instanceof HttpHeaderResponse),
      map((event: HttpEvent<any>) => {
        if (event instanceof HttpResponse && event.body) {
          if (!environment.production) return event;
          if (!event.body || !event.body.data || !event.body.secret) return event;
          const decryptedData = this.decryptResponse(event.body);
          return event.clone({
            body: decryptedData,
            headers: event.headers,
            status: event.status,
            statusText: event.statusText,
          });
        }

        return event;
      }),
    );
  }

  private decryptResponse(body: any): any {
    const decryptedData = CryptoJS.AES.decrypt(body.data, body.secret).toString(CryptoJS.enc.Utf8);
    return JSON.parse(decryptedData);
  }
}
