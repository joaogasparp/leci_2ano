#include <detpic32.h>

void delay(int ms);

int main(void)
{
    TRISDbits.TRISD8 = 1;
    TRISEbits.TRISE0 = 0;

    while(1)
    {
        LATEbits.LATE0 = 0;
        if((PORTD & 0x0100) == 1)
        {
            LATEbits.LATE0 = 1;
            delay(3000);
        }
    }
    return 0;
}

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}
