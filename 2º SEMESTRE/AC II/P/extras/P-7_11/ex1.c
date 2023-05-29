#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    // ports
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    LATEbits.LATE3 = 0;
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;

    while (1)
    {
        char c = getChar();
        if(c == '0')
        {
            LATE = LATE & 0x0001;
        }else if(c == '1')
        {
            LATE = LATE & 0x0002;
        }else if(c == '2')
        {
            LATE = LATE & 0x0004;
        }else if(c == '3')
        {
            LATE = LATE & 0x0008;
        }else
        {
            LATE = LATE & 0x000F;
            delay(10);
            LATE = LATE & 0xFFF0;
        }
    }

    return 0;
}