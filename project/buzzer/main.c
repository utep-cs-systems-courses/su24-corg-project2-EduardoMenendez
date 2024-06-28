#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "notes.h"
#define SWITCHES 15



//int song[] = {A, A, D, D, F, A, A,D,F,A,C,B,G,F,G,A,D,C,E,D,G,A,D,E,D,A,A,D,D,F};
int song[] = {D,B,F,F,E,D,B,E,E,D,C,B,D,B,D,E,C,A,A,E,D};
//int song[] = {B,A,F,B,A,F,B,A,E,D,E,B,A,F,B,A,F,B,E,D,E,F,C,B,F,C,B,F,E,B,A,B,F,C,B,F,E,B,G,A,A,D,D};
int counter = 0;
void musicState();

int main(){
    configureClocks();
    enableWDTInterrupts();

    buzzer_init();

    or_sr(0x18);
}

void __interrupt_vec(WDT_VECTOR) WDT(){
    musicState();
}
int i = 0;
void musicState(){
    
    counter++;
    if(counter>=50){
        counter = 0;
        buzzer_set_period(song[i]);
        i++;
        if(song[i]== '\0'){
            i=0;
        }
    }
}

