
#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "notes.h"
void init_buttons(){
  P2REN |= SWITCHES;       
  P2IE |= SWITCHES;       
  P2OUT |= SWITCHES;     
  P2DIR &= ~SWITCHES;   
}

static char switch_update_interrupt_sense(){
    char p2val = P2IN;
    P2IES |= (p2val & SWITCHES);    
    P2IES &= (p2val | ~SWITCHES); 

    return p2val;
}

void switch_interrupt_handler(){
    char p2val = switch_update_interrupt_sense();
    int switches = ~p2val & SWITCHES;
    if(switches & SWITCHES){
        for(char swNum = 0; swNum < 3; swNum++){
            int swFlag = 1<<swNum;
            if(switches&swFlag){
             currSong = swNum;   
             break;
            }
        }
    }
}
