#include <detpic32.h>

void delay(unsigned int ms);

int main(void) {

    LATE = LATE & 0xFFC3;   // 1111 1111 1100 0011

    TRISE = TRISE & 0xFFC3; // saída
    TRISB = TRISB & 0x0004; // entrada

    int counter = 0, freq = 0;

    while(1) {
        LATE = (LATE & 0xFFC3) | (counter << 2);

        if(--counter<0) counter = 12;

        if(PORTBbits.RB2 == 0) freq = 8695652;
        if(PORTBbits.RB2 == 1) freq = 3636363;

        delay(freq);

        printInt(counter, 10 | 2 << 10);
        putChar('\n');
    }

    return 0;
}

void delay(unsigned int f) {
    resetCoreTimer();
    while(readCoreTimer() < f);
}
