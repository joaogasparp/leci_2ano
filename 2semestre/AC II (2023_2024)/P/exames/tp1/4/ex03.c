#include <detpic32.h>

void delay(unsigned int ms);

int main(void) {
    LATE = LATE & 0xFFC1;   // 1111 1111 1100 0001
    TRISE = TRISE & 0xFFC1;

    int seq = 0x02; // 0000 0010

    while(1) {
        LATE = (LATE & 0xFFC1) | seq;
        seq = seq << 1;
        printInt(seq, 2 | 5 << 16);
        putChar('\n');

        delay(8695652);

        if(seq > 0x20) seq = 0x02; // 10 0000
    }

    return 0;
}

void delay(unsigned int freq) {
    resetCoreTimer();
    while(readCoreTimer() < freq);
}
