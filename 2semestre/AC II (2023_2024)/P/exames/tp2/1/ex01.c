#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    TRISD = TRISD | 0x0005; // 1 quando é entrada

    T3CONbits.TCKPS = 2; // 20000000 / (65536 * 120) = 2.5 -> 4 (010)
    PR3 = 41666;         // PR3 = ((20000000 / 4) / 120) - 1 = 41666
    TMR3 = 0;
    T3CONbits.TON = 1;

    OC2CONbits.OCM = 6;
    OC2CONbits.OCTSEL = 0;
    OC2RS = 31250; // ((PR3 + 1) * 75) / 100 = 31250
    OC2CONbits.ON = 1;

    while (1)
    {
        if (PORTBbits.RB2 == 0 && PORTBbits.RB0 == 0)
        {
            OC2RS = 12500; // ((PR3 + 1) * 30) / 100 = 12500
        }
        else if (PORTBbits.RB2 == 1 && PORTBbits.RB0 == 1)
        {
            OC2RS = 22917; // ((PR3 + 1) * 55) / 100 = 22917
        }
        delay(360000);
    }

    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while (readCoreTimer() < 20000 * ms)
        ;
}
