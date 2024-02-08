export class UrlUtil {
  static buildUrl(base: string, path: string, queryParams: Record<string, unknown> = {}): string {
    const url = new URL(path, base);
    Object.entries(queryParams).forEach(([key, value]) => url.searchParams.append(key, `${value}`));
    return `${url}`;
  }
}
