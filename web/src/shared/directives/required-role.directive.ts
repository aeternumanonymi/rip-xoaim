import { Directive, ElementRef, Input, OnChanges, OnInit } from '@angular/core';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';

import { UserService } from '@api/services';
import { AppUserDto } from '@api/dtos';

@Directive({
  selector: '[requiredRole]',
})
export class RequiredRoleDirective implements OnInit, OnChanges {
  @Input('requiredRole') role!: string;

  public me!: AppUserDto | null;

  constructor(private readonly elementRef: ElementRef, private readonly userService: UserService) {}

  public ngOnInit(): void {
    this.elementRef.nativeElement.style.display = 'none';
    this.userService.me.pipe(takeUntilDestroyed()).subscribe((me: AppUserDto | null) => {
      this.me = me;
      this.checkAccess();
    });
  }

  public ngOnChanges(): void {
    this.checkAccess();
  }

  public checkAccess(): void {
    const hasRequiredRole = this.me?.role === this.role;
    this.elementRef.nativeElement.style.display = hasRequiredRole ? 'block' : 'none';
  }
}
