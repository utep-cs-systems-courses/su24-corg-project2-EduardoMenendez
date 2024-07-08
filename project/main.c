#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "notes.h"
#include "switches.h"

int song[] = {A, A, D, D, F, A, A,D,F,A,C,B,G,F,G,A,D,C,E,D,G,A,D,E,D,A,A,D,D,F};
int song2[] = {D,B,F,F,E,D,B,E,E,D,C,B,D,B,D,E,C,A,A,E,D};
int song3[] = {B,A,F,B,A,F,B,A,E,D,E,B,A,F,B,A,F,B,E,D,E,F,C,B,F,C,B,F,E,B,A,B,F,C,B,F,E,B,G,A,A,D,D};
int* songs[] = {song, song2, song3};
int counter = 0;
void musicState();
int i = 0;

int main(){
    configureClocks();
    enableWDTInterrupts();
    init_buttons(); 
    currSong = 0;

    buzzer_init();

    or_sr(0x18);
}

void __interrupt_vec(WDT_VECTOR) WDT(){
    if(P2IFG & SWITCHES){
        P2IFG = ~SWITCHES;
        switch_interrupt_handler();
    }else
        musicState();
}
void musicState(){

    counter++;
    if(counter>=50){
        counter = 0;
        buzzer_set_period(songs[currSong][i]);
        i++;
        if(song[i]== '\0'){
            i=0;
        }
    }
}

