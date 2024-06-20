#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    unsigned char segment;

    // enable display low (RD5) and disable display high (RD6)
    LATD = LATD | 0x0020;       // 0000 0000 0010 0000

    // configure RB8-RB14 as outputs
    LATB = (LATB & 0x80FF);     // 1000 0000 1111 1111
    TRISB = (TRISB & 0x80FF);   // 1000 0000 1111 1111

    // configure RD5-RD6 as outputs
    LATD = (LATD & 0xFF9F);     // 1111 1111 1001 1111
    TRISD = (TRISD & 0xFF9F);   // 1111 1111 1001 1111

    while(1)
    {
        segment = 1;
        int i;
        for(i = 0; i < 7; i++)
        {
            // send "segment" value to display
            LATB = (LATB & 0x80FF) | (segment << 8);
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

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
