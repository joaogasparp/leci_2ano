#include <detpic32.h>

void delay(unsigned int ms);
void send2displays(unsigned int val);

int main(void) {

    LATE = LATE & 0xFFC3;   // 1111 1111 1100 0011

    TRISE = TRISE & 0xFFC3; // saída
    TRISB = TRISB | 0x0004; // entrada

    int counter = 0, freq;

    while(1) {
        LATE = (LATE & 0xFFC3) | (counter << 2)

        if(++counter>12) counter = 0;

        if(PORTBbits.RB2 == 0) freq = 
        if(PORTBbits.RB2 == 1) freq = 

        delay();

        printInt(counter, 10 | 2 << 10);
        putChar('\n');
    }

    return 0;
}

void send2displays(unsigned int val) {

    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    int static flag = 0;

    int digitLow = val % 16;
    int digitHigh = val / 16;

    if(flag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[digitLow] << 8);
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[digitHigh] << 8);
    }
    flag = !flag;
}

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
