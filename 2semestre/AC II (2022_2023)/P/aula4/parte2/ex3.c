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

    LATD = (LATD | 0x0020);     // 0000 0000 0010 0000

    while(1)
    {
        segment = 1;
        for(int i = 0; i < 7; i++)
        {
            LATB = (LATB & 0x80FF) | (segment << 8);
            delay(500);
            segment = segment << 1;
        }
        LATD = LATD ^ 0x0060    // 0000 0000 0110 0000
    }
    return 0;
}
