#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    LATE = LATE & 0xFFF0;

    TRISE = TRISE & 0xFFF0;
    TRISB = TRISB | 0x000F;

    while(1)
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
            delay(1000);
            LATE = LATE & 0xFFF0;
        }
        putChar('\r');
    }  
    return 0;
}
