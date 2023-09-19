#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    unsigned char segment;
    LATB = (LATB & 0x80FF);     // 1000 0000 1111 1111
    TRISB = (TRISB & 0x80FF);
    LATD = (LATD & 0xFF9F);     // 1111 1111 1001 1111    
    TRISD = (TRISD & 0xFF9F);

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1)
    {
        segment = 1;
        for(int i = 0; i < 7; i++)
        {
            LATB = (LATB & 0x80FF) | (segment << 8);
            delay(100);     // 20,10
            segment = segment << 1;
        }
        LATDbits.LATD5 = !LATDbits.LATD5;
        LATDbits.LATD6 = !LATDbits.LATD6;
    }
    return 0;
}
