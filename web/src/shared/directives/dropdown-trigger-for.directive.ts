import { Directive, ElementRef, Input, OnDestroy, ViewContainerRef } from '@angular/core';
import { Overlay, OverlayRef } from '@angular/cdk/overlay';
import { TemplatePortal } from '@angular/cdk/portal';
import { merge, Observable, Subscription } from 'rxjs';

import { DropdownPanel } from '@shared/interfaces';

@Directive({
  selector: '[dropdownTriggerFor]',
  host: {
    '(click)': 'toggleDropdown()',
  },
})
export class DropdownTriggerForDirective implements OnDestroy {
  @Input('dropdownTriggerFor') public dropdownPanel!: DropdownPanel;

  private isDropdownOpen: boolean = false;
  private overlayRef!: OverlayRef;
  private dropdownClosingActionsSub: Subscription = Subscription.EMPTY;

  constructor(
    private readonly overlay: Overlay,
    private readonly elementRef: ElementRef<HTMLElement>,
    private readonly viewContainerRef: ViewContainerRef,
  ) {}

  public toggleDropdown(): void {
    this.isDropdownOpen ? this.destroyDropdown() : this.openDropdown();
  }

  public openDropdown(): void {
    this.isDropdownOpen = true;
    this.overlayRef = this.overlay.create({
      hasBackdrop: true,
      backdropClass: 'cdk-overlay-transparent-backdrop',
      scrollStrategy: this.overlay.scrollStrategies.close(),
      positionStrategy: this.overlay
        .position()
        .flexibleConnectedTo(this.elementRef)
        .withPositions([
          {
            originX: 'end',
            originY: 'bottom',
            overlayX: 'end',
            overlayY: 'top',
            offsetY: 8,
          },
        ]),
    });

    const templatePortal = new TemplatePortal(this.dropdownPanel.templateRef, this.viewContainerRef);
    this.overlayRef.attach(templatePortal);

    this.dropdownClosingActionsSub = this.dropdownClosingActions().subscribe(() => this.destroyDropdown());
  }

  private dropdownClosingActions(): Observable<unknown> {
    const backdropClick$ = this.overlayRef.backdropClick();
    const detachment$ = this.overlayRef.detachments();
    const dropdownClosed = this.dropdownPanel.closed;

    return merge(backdropClick$, detachment$, dropdownClosed);
  }

  private destroyDropdown(): void {
    if (!this.overlayRef || !this.isDropdownOpen) {
      return;
    }

    this.dropdownClosingActionsSub.unsubscribe();
    this.isDropdownOpen = false;
    this.overlayRef.detach();
  }

  public ngOnDestroy(): void {
    if (this.overlayRef) {
      this.overlayRef.dispose();
    }
  }
}
