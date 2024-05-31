#include <detpic32.h>

void send2displays(unsigned int val);
void delay(unsigned int ms);

volatile int temp;

int main(void)
{
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 2 - 1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    T2CONbits.TCKPS = 2; // 20000000 / (65536 * 120) = 2,5 -> 4 (010)
    PR2 = 41666;         // ((20000000 / 4) / 120) - 1 = 41666
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    EnableInterrupts();

    while (1)
    {
        AD1CON1bits.ASAM = 1;
        while (IFS1bits.AD1IF == 0)
            ;

        int media = (ADC1BUF0 + ADC1BUF1) / 2;
        temp = (media * (0x65 - 0x15) / 1023) + 0x15;

        IFS1bits.AD1IF = 0;
        delay(100);
    }

    return 0;
}

void _int_(8) isr_T2(void)
{
    send2displays(temp);
    IFS1bits.AD1IF = 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while (readCoreTimer() < 20000 * ms)
        ;
}

void send2displays(unsigned int val)
{

    int static segments[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0xE5, 0x79, 0x71};
    int static flag = 0;

    int digitLow = val % 16;
    int digitHigh = val / 16;

    if (flag == 0)
    {
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[digitLow] << 8);
    }
    else
    {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[digitHigh] << 8);
    }
    flag = !flag;
}
