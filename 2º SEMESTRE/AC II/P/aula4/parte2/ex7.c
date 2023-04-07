#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    static const char disp7scodes[] = {0x3F,0x06,0x5B,
    0x4F,0x66,0x6D,
    0x7C,0x07,0x7F,
    0x67,0x5F,0x7C,
    0x39,0x5E,0x79,0x71};

    LATB = (LATB & 0x80FF);             // reset do LATB8 A LATB14
    LATD = (LATD & 0xFF9F);             // reset do LATD5 A LATD6

    TRISB = (TRISB & 0x80FF);           // configure RB8 to RB14 as outputs
    TRISD = (TRISD & 0xFF9F);           // configure RD5 to RD6 as outputs
    TRISB = (TRISB | 0x000F);           // configure RB0 to RB3 as inputs
    
    LATDbits.LATD6 = 1;                 // Select display low

    while(1)
    {
        int index = PORTB & 0x000F;         // read dip-switch
        int num = display7scodes[index];    // convert to 7 segments code
        LATB = num << 8;// send to display
    }
    return 0;
}
