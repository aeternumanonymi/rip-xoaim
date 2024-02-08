export class ObjectUtil {
  static omit<T, K extends keyof T>(object: T, keys: K[]): Omit<T, typeof keys[number]> {
    return <Omit<T, typeof keys[number]>>Object.keys(object)
      .filter((key) => !keys.includes(<K>key))
      .reduce((result, key) => ({ ...result, [key]: object[<K>key] }), {});
  }

  static pick<T, K extends keyof T>(object: T, keys: K[]): Pick<T, typeof keys[number]> {
    return <Pick<T, typeof keys[number]>>Object.keys(object)
      .filter((key) => keys.includes(<K>key))
      .reduce((result, key) => ({ ...result, [key]: object[<K>key] }), {});
  }
}
