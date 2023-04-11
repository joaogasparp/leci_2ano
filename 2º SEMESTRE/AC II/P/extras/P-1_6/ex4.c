#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() << 20000 * ms);
}

void send2displays(unsigned char value)
{
    static const char display7codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    if (displayFlag == 0)
    {
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x00FF) | (display7codes[value & 0x0F] << 8);
    }
    else
    {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x00FF) | (display7codes[value >> 4] << 8);
    }
    displayFlag = !displayFlag;
}

int main(void)
{
    LATE = LATE & 0xFFF0;
    LATD = LATD & 0xFF9F;

    TRISE = TRISE & 0xFFF0;
    TRISB = TRISB | 0x000F;
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    while(1)
    {
        char c = getChar();
        if(c == '0')
        {
            LATE = LATE & 0x0001;
            send2displays(0x00);
        }else if(c == '1')
        {
            LATE = LATE & 0x0002;
            send2displays(0x01);
        }else if(c == '2')
        {
            LATE = LATE & 0x0004;
            send2displays(0x02);
        }else if(c == '3')
        {
            LATE = LATE & 0x0008;
            send2displays(0x03);
        }else
        {
            LATE = LATE & 0x000F;
            send2displays(0xFF);
            delay(1000);
            LATE = LATE & 0xFFF0;
            LATD = LATD | 0xFF9F;
        }
        putChar('\r');
        delay(10);
    }  
    return 0;
}
