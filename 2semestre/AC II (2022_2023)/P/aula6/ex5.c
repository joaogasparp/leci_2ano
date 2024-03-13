#include <detpic32.h>

int main(void)
{
    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0;      // RB4 configured as analog input
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this
                                // mode an internal counter ends sampling and
                                // starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time,
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 3;       // Interrupt is generated after N samples
    AD1CHSbits.CH0SA = 4;       // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter

    int voltage = 0;

    while(1)
    {
        AD1CON1bits.ASAM = 1;           // Start conversion
        while(IFS1bits.AD1IF == 0);     // Wait while conversion not done (AD1IF == 0)
        int *p = (int *)(&ADC1BUF0);
        for( int i = 0; i < 4; i++ )
        {
            voltage += (p[i*4]*33+511) /1023;
        }
        printInt(voltage / 4,10 | 2 << 16);
        IFS1bits.AD1IF = 0;
    }
    return 0;
}