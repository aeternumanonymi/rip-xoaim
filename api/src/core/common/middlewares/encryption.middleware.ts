import { Injectable, NestMiddleware } from '@nestjs/common';
import { Response } from 'express';
import * as cryptoJs from 'crypto-js';
import * as crypto from 'crypto';

@Injectable()
export class EncryptionMiddleware implements NestMiddleware {
  use(req: any, res: Response, next: () => void) {
    const originalSend = res.send;

    res.send = function (body) {
      if (!body) originalSend.call(this, body);
      if (process.env.NODE_ENV === 'production') {
        const encryptedResponse = encrypt(body);
        originalSend.call(this, JSON.stringify(encryptedResponse));
      } else {
        originalSend.call(this, body);
      }
    } as any;

    if (next) {
      next();
    }
  }
}

function encrypt(data: any): { secret: string; data: string } {
  const secret = crypto.randomBytes(32);
  const encryptedData = cryptoJs.AES.encrypt(data, secret.toString('hex')).toString();

  return {
    secret: secret.toString('hex'),
    data: encryptedData,
  };
}
