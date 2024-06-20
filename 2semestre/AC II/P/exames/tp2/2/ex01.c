#include <detpic32.h>

int main(void)
{
    TRISB = TRISB & 0x0009;

    T2CONbits.TCKPS = 2; // 20000000 / (65536 * 150) = 2 -> 4 (010)
    PR2 = 33332;         // ((20000000 / 4) / 150) - 1 = 33332
    TMR2 = 0;
    T2CONbits.TON = 1;

    OC2CONbits.OCM = 6;
    OC2CONbits.OCTSEL = 0;
    OC2RS = 8333; // (33333 * 25) / 100 = 8333
    OC2CONbits.ON = 1;

    while (1)
    {
        if (PORTBbits.RB3 == 0 && PORTBbits.RB0 == 1)
        {
            OC2RS = 8333;
        }
        else if (PORTBbits.RB3 == 1 && PORTBbits.RB0 == 0)
        {
            OC2RS = 23333; // (33333 * 70) / 100 = 23333
        }
        delay(250);
    }

    return 0;
}

void delay(unsigned int us)
{
    resetCoreTimer();
    while (readCoreTimer() < 20 * us)
        ;
}
