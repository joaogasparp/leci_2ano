#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

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
    AD1CON2bits.SMPI = 0;       // Interrupt is generated after N samples
    AD1CHSbits.CH0SA = 4;       // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter
    while(1)
    {
        AD1CON1bits.ASAM = 1;           // Start conversion
        while(IFS1bits.AD1IF == 0);     // Wait while conversion not done (AD1IF == 0)
        printInt(ADC1BUF0, 10);
        putChar('\n');
        delay(1000);
    }
    return 0;
}