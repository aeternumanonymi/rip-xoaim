export interface HttpOptions {
  readonly headers?: { [key: string]: string | string[] };
  readonly query?: { [key: string]: string | string[] };
  readonly contentType?: 'application/json' | 'multipart/form-data';
}
