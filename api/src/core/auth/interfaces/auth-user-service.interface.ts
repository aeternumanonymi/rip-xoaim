import { AuthUserDto } from '../dtos';

export interface AuthUserService {
  findOneById(id: number): Promise<AuthUserDto | null>;
  findOneByUsernameAndPassword(username: string, password: string): Promise<AuthUserDto | null>;
}
