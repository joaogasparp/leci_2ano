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
    LATD = (LATD | 0x0020);

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
    LATD = LATD ^ 0x0060;
    }
    return 0;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}