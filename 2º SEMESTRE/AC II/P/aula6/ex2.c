#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    volatile int aux;
    // Configure A/D module; configure RD11 as a digital output port
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;
    TRISDbits.TRISD11 = 0;
    while(1)
    {
        AD1CON1bits.ASAM = 1;
        LATDbits.LATD11 = 1;
        while(IFS1bits.AD1IF == 0);
        LATDbits.LATD11 = 0;
        aux = ADC1BUF0;
        IFS1bits.AD1IF == 0;
    }
    return 0;
}