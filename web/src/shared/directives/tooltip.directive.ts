import { Directive, ElementRef, HostListener, Injector, Input, OnDestroy, TemplateRef, ViewContainerRef } from '@angular/core';
import { Overlay, OverlayRef, PositionStrategy } from '@angular/cdk/overlay';
import { ComponentPortal } from '@angular/cdk/portal';

import { TooltipComponent, TOOLTIP_DATA } from '@shared/components';

@Directive({
  selector: '[xoTooltip]',
})
export class TooltipDirective implements OnDestroy {
  @Input() xoTooltip!: string | TemplateRef<void>;

  private overlayRef: OverlayRef | null = null;

  constructor(private element: ElementRef<HTMLElement>, private overlay: Overlay, private viewContainer: ViewContainerRef) {}

  @HostListener('mouseenter')
  @HostListener('focus')
  showTooltip(): void {
    if (!this.xoTooltip) {
      return;
    }

    if (this.overlayRef?.hasAttached() === true) {
      return;
    }

    this.attachTooltip();
  }

  @HostListener('mouseleave')
  @HostListener('blur')
  hideTooltip(): void {
    if (this.overlayRef?.hasAttached() === true) {
      this.overlayRef?.detach();
    }
  }

  public ngOnDestroy(): void {
    this.overlayRef?.dispose();
  }

  private attachTooltip(): void {
    if (this.overlayRef === null) {
      const positionStrategy = this.getPositionStrategy();
      this.overlayRef = this.overlay.create({ positionStrategy });
    }

    const injector = Injector.create({
      providers: [
        {
          provide: TOOLTIP_DATA,
          useValue: this.xoTooltip,
        },
      ],
    });
    const component = new ComponentPortal(TooltipComponent, this.viewContainer, injector);
    this.overlayRef.attach(component);
  }

  private getPositionStrategy(): PositionStrategy {
    return this.overlay
      .position()
      .flexibleConnectedTo(this.element)
      .withPositions([
        {
          originX: 'center',
          originY: 'top',
          overlayX: 'center',
          overlayY: 'bottom',
          panelClass: 'top',
        },
        {
          originX: 'center',
          originY: 'bottom',
          overlayX: 'center',
          overlayY: 'top',
          panelClass: 'bottom',
        },
      ]);
  }
}
