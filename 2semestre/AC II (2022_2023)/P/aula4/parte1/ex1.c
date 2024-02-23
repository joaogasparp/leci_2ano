#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    LATCbits.LATC14 = 0; // reset
    TRISCbits.TRISC14 = 0; // configura o porto RC14 como output
    while(1)
    {
        delay(500); // wait 0.5s
        LATCbits.LATC14 = ! LATCbits.LATC14;
    }
    return 0;
}
