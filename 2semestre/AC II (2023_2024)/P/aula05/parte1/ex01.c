#include <detpic32.h>

void send2displays(unsigned char value)
{
    static const char disp7scodes[] = {0x3F,0x06,0x5B,
        0x4F,0x66,0x6D,
        0x7C,0x07,0x7F,
        0x67,0x5F,0x7C,
        0x39,0x5E,0x79,0x71};

    LATDbits.LATD6 = !LATDbits.LATD6;       // toggle display high   0 | 1
    LATDbits.LATD5 = !LATDbits.LATD5;       // toggle display low    1 | 0

    if(LATDbits.LATD6 == 1)                 // select display high
    {
        LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0xF0) >> 4] << 8);        // send digit_high (dh) to display: dh = value >> 4
    }else                                   // select display low
    {
        LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0x0F)] << 8);                 // send digit_low (dl) to display:  dl = value & 0x0F
    }
}
