import { animate, state, style, transition, trigger } from '@angular/animations';
import { Component } from '@angular/core';

@Component({
  selector: 'xo-faq',
  templateUrl: './faq.component.html',
  styleUrls: ['./faq.component.scss'],
  animations: [
    trigger('expandCollapse', [
      state('false', style({ height: '0', overflow: 'hidden', padding: '0 40px' })),
      state('true', style({ height: '*' })),
      transition('* <=> *', animate('200ms ease-in-out')),
    ]),
  ],
})
export class FAQComponent {
  public questions: { title: string; body: string; expanded: boolean }[] = [
    { title: 'Will I get banned for using this cheat?', body: 'No', expanded: true },
    { title: 'How much does it cost?', body: '40€ / month', expanded: false },
    { title: 'Can I use this cheat on FACEIT?', body: 'No', expanded: false },
    { title: 'How can I purchase this cheat?', body: 'No', expanded: false },
    { title: 'Is it possible to refund my purchase?', body: 'No', expanded: false },
    { title: 'What features does this cheat have?', body: 'Aimbot, triggerbot, utility, idler.', expanded: false },
    { title: 'Will there be any additional features added, like wallhack?', body: 'No, never.', expanded: false },
  ];

  public toggleQuestionExpand(question: { title: string; body: string; expanded: boolean }): void {
    this.questions.forEach((q) => (q.expanded = false));
    question.expanded = !question.expanded;
  }
}
