#include <detpic32.h>

void delay(int ms);

int main(void){
    unsigned char segment;

    //reset
    LATD = (LATD & 0xFF9F);
    LATB = (LATB & 0x80FF);
    // Configure ports
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    //configure dysplay
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1){
        segment = 1;
        int i;
        for(i=0; i < 7; i++){
        // send "segment" value to display
        LATB = (LATB & 0x80FF ) | segment <<8;
        // wait 0.5 second
        delay(500);
        segment = segment << 1;
    }
    // toggle display selection
    LATDbits.LATD5 = !LATDbits.LATD5;
    LATDbits.LATD6 = !LATDbits.LATD6;
    }
    return 0;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}