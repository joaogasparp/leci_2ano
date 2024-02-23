#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void send2Displays(unsigned int val)
{
    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0xE5,0x79,0x71};
    int static flag = 0;

    int digitLow = val % 16;
    int digitHigh = val / 16;

    if(flag == 0)
    {
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[digitLow] << 8); 
    }else {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[digitHigh] << 8); 
    }
    flag = !flag;
}

int main(void)
{
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    int counter = 20;
    double freq, t;
    volatile int aux;
    while(1)
    {
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);
        aux = ADC1BUF0;
        IFS1bits.AD1IF == 0;

        freq = 1 + (aux / 255);    // 1/f * 1000 = t
        t = 1/freq * 1000;

        int i = 0;
        do
        {
            send2Displays(counter);
            delay(20);
        } while (++i < (t / 20));        // 20 * x = 1/freq * 1000

        counter = (counter - 1) % 20;
        if(counter == 0) counter = 20;
    }
    return 0;
}
