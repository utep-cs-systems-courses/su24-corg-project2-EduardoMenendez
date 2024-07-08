#ifndef switch_included
#define switch_included
#define SWITCHES (BIT0 | BIT1 | BIT2 | BIT3)

void init_buttons();
static char switch_update_interrupt_sense();
void switch_interrupt_handler();

#endif
