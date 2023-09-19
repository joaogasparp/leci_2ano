#include <detpic32.h>
void delay(int ms)
{
    for (; ms > 0; ms--)
    {
        resetCoreTimer();
        while (readCoreTimer() < 20000) ;
    }
}

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value)
{
    static const char display7codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    if (displayFlag == 0)
    {
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;

        LATB = (LATB & 0x00FF) | (display7codes[value & 0x0F] << 8);
    }
    else
    {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;

        LATB = (LATB & 0x00FF) | (display7codes[value >> 4] << 8);
    }

    displayFlag = !displayFlag;
}

int main(void)
{

    //Definir RB8 a RB15 como 0

    TRISB = (TRISB & 0x00FF);

    TRISDbits.TRISD5 = 0; // RD5 como saida
    TRISDbits.TRISD6 = 0; // RD6 como saida

    LATB = LATB & 0x00FF;

    TRISBbits.TRISB4 = 1;     // RBx digital output disconnected
    AD1PCFGbits.PCFG4 = 0;    // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this
                              //  mode an internal counter ends sampling and
                              //  starts conversion
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter
                              //  interrupt is generated. At the same time,
                              //  hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 2 - 1; // Interrupt is generated after XX samples
                              //  (replace XX by the desired number of
                              //  consecutive samples)
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input
                              //  analog channel (0 to 15)
    AD1CON1bits.ON = 1;       // Enable A/D converter
                              //  This must the last command of the A/D
                              //  configuration sequence
    double media = 0;
    while (1)
    {
        // Start conversion
        AD1CON1bits.ASAM = 1;
        // Wait while conversion not done (AD1IF == 0)
        while (IFS1bits.AD1IF == 0)
            ;

        int *p = (int *)(&ADC1BUF0);
        int i = 0;
        for (; i < 2; i++)
        {
            media += p[i * 4];
        }

        media = media/2;

        media = (media*33)/1023;

        printInt((int) media,(3 << 16)| 16);
        printStr("\n");

        if (media < 1.2)
        {
            send2displays(0x0A);
            delay(10);
        }
        else
        {
            send2displays(0xB0);
            delay(10);
        }
        
    }

    return 0;
}
