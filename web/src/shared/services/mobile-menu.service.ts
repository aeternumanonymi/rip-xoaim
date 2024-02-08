import { Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class MobileMenuService {
  public isMenuOpen = new BehaviorSubject<boolean>(false);

  public toggleVisibility(status?: boolean): void {
    const newStatus = status === undefined ? !this.isMenuOpen.getValue() : status;
    this.isMenuOpen.next(newStatus);
  }

  get status(): Observable<boolean> {
    return this.isMenuOpen.asObservable();
  }
}
