#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    LATEbits.LATE6 = 0; // reset
    TRISEbits.TRISE6 = 0; // configura o porto REx como output
    LATEbits.LATE5 = 0; // reset
    TRISEbits.TRISE5 = 0; // configura o porto REx como output
    LATEbits.LATE4 = 0; // reset
    TRISEbits.TRISE4 = 0; // configura o porto REx como output
    LATEbits.LATE3 = 0; // reset
    TRISEbits.TRISE3 = 0; // configura o porto REx como output
    int count = 0;
    while(1)
    {
        LATE = (LATE & 0xFF87) | (count << 6);
        LATE = (LATE & 0xFF87) | (count << 5);
        LATE = (LATE & 0xFF87) | (count << 4);
        LATE = (LATE & 0xFF87) | (count << 3);
        delay(250);
        count++;
        if(count == 10) count = 0;
    }
    return 0;
}