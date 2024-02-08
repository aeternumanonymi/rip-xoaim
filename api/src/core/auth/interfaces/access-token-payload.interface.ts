export interface AccessTokenPayload {
  // Subject
  // https://tools.ietf.org/html/rfc7519#section-4.1.2
  readonly sub: number;
  readonly role: string;
}
