#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    TRISB = TRISB & 0x0006;

    T3CONbits.TCKPS = 2;   // 20000000/(65536*130)
    PR3 = 38461;           // ((20000000/4)/130)-1=38461
    TMR3 = 0;              // Reset timer T2 count register
    T3CONbits.TON = 1;     // Enable timer T2 (must be the last command of the
                           //  timer configuration sequence)
    OC4CONbits.OCM = 6;    // PWM mode on OCx; fault pin disabled
    OC4CONbits.OCTSEL = 0; // Use timer T2 as the time base for PWM generation
    OC4RS = 19231;         // (38462*50)/100
    OC4CONbits.ON = 1;

    while (1)
    {
        if (PORTBbits.RB1 == 0 && PORTBbits.RB2 == 0)
        {
            OC4RS = 9616;
            delay(1300);
            OC4RS = 28847;
        }
    }
    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while (readCoreTimer() < 20000 * ms)
        ;
}
