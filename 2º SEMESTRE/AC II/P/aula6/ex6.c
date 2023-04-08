#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value)
{
    static const char disp7scodes[] = {0x3F,0x06,0x5B,
        0x4F,0x66,0x6D,
        0x7C,0x07,0x7F,
        0x67,0x5F,0x7C,
        0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;

    if(displayFlag == 0)                    // if "displayFlag" is 0 then send digit_low to display_low
    {
        LATB = (LATB & 0xFF9F) | 0x0020;    // dar reset
        digit_low = disp7scodes[digit_low];
        LATB = (LATB & 0X80FF) | (digit_low << 8);
    }else                                   // select display low
    {
        LATB = (LATB & 0x80FF) | 0x0040;    // dar reset
        digit_high = disp7scodes[digit_high];
        LATB = (LATB & 0X80FF) | (digit_high << 8);
    }

    displayFlag = ! displayFlag;
}

int main(void)
{
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    int i = 0, voltage = 0;

    while(1)
    {
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);
        if(i == 0)
        {
            int *p = (int *)(&ADC1BUF0);
            for( int i = 0; i < 4; i++ )
            {
                voltage += (p[i*4]*33+511) /1023;
            }
            IFS1bits.AD1IF = 0;
        }
        send2displays(toBcd(voltage/4));
        delay(10);
        i = (i + 1) % 20;               // para ser 200ms 10*20
    }
    return 0;
}
