#include <detpic32.h>

void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x5F, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // Lista de caracteres

    if(LATDbits.LATD6 == 1)
    {
        LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0xF0) >> 4] << 8);
    } else
    {
        LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0x0F)] << 8);
    }

    // select display high
    // send digit_high (dh) to display: dh = value >> 4
    // select display low
    // send digit_low (dl) to display:  dl = value & 0x0F
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    LATD = (LATD & 0xFF9F);
    LATB = (LATB & 0x80FF);

    TRISD = (TRISD & 0xFF9F);           // configure RD5-RD6 as outputs
    TRISB = (TRISB & 0x80FF);           // configure RB8-RB14 as outputs

    while(1)
    {
        send2displays(0x15);
        delay(200);
    }
    return 0;
}