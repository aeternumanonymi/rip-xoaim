export interface ApiConfig {
  readonly corsOrigin: string | string[];
  readonly documentationEnabled: boolean;
  readonly webUrl: string;
  readonly apiUrl: string;
  readonly encryptionKey: string;
  readonly port: number;
}
