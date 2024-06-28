#include <msp430.h>
#include "libTimer.h"

#define LED_GREEN BIT6
#define LED_RED BIT0
#define LEDS (BIT0 | BIT6)

#define SWITCH BIT3
#define SWITCHES SWITCH

void state_switch();
void state_bin();

void main(){
    configureClocks();

    P1DIR |= LEDS;
    P1OUT &= ~LEDS;

    P1REN |= SWITCHES;
    P1IE |= SWITCHES;
    P1OUT |= SWITCHES;
    P1DIR &= ~SWITCHES;

    or_sr(0x18);
}

void switch_interrupt_handler(){
    char pival = P1IN;
    P1IES |= (pival & SWITCHES);
    P1IES &= (pival | ~SWITCHES);
    if(!(pival & SWITCH)){
        //state_switch();
        state_bin();
   }
}

void __interrupt_vec(PORT1_VECTOR) Port_1(){
    if(P1IFG & SWITCHES){
        switch_interrupt_handler();
    }
}

int state = 0;

void state_bin(){
    P1OUT &= ~LED_RED;
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED&(state);
    P1OUT |= (LED_GREEN)&(state<<5);
    state++;
    if(state>=4){
        state = 0;
    }
}


void state_switch(){
    switch(state){
        case 0:
            P1OUT &= ~LED_GREEN;
            P1OUT &= ~LED_RED;
            break;
        case 1:
            P1OUT &= ~LED_GREEN;
            P1OUT |= LED_RED;
            break;
        case 2:
            P1OUT |= LED_RED;
            P1OUT &= ~LED_GREEN;
            break;
        case 3:
            P1OUT |= LED_RED;
            P1OUT |= LED_GREEN;
            break;
        default:
            state = -1;
    }
    state = state+1;
}
