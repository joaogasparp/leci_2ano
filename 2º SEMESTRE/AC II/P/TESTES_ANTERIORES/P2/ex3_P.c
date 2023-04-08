#include <detpic32.h>

void delay(int ms)
{

    for (; ms > 0; ms--)
    {

        resetCoreTimer();
        while (readCoreTimer() < 20000)
            ;
    }
}

void send2displays(unsigned char value)
{

    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                                          0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag;

    int display_low = value & 0x0F;
    int display_high = value >> 4;

    if (displayFlag == 0)
    {
        LATB = (LATB & 0x00FF) | display7Scodes[display_low] << 8;
        LATDbits.LATD5 = 1; 
        LATDbits.LATD6 = 0;
 
    }
    else
    {
        LATB = (LATB & 0x00FF) | display7Scodes[display_high] << 8;
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;

    }

    displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value)
{
	return ( (value / 10 ) << 4) + (value % 10); 
}

int main(void)
{

    TRISBbits.TRISB4 = 1;  // RBx digital output disconnected
    AD1PCFGbits.PCFG4 = 0; // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;  // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;     // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 1 - 1; // Interrupt is generated after XX samples
    // (replace XX by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
                        // This must the last command of the A/D
                        // configuration sequence


    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;


    int count = 19;
    int countBCD = 0;
    int contador = 0;

    int freq = 0;
    int periodo = 0;

    while (1)
    {
        send2displays(countBCD);
		printf("freq=%d | ms=%d \n",freq,periodo);
		delay(1000);
		
        delay(20);

        AD1CON1bits.ASAM = 1; // Start conversion

        while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done 

        freq = 1 + (ADC1BUF0/255);
        periodo = 50/freq;      // PORQUE ESTAMOS COM UM DELAY DE 20ns (50 hz)

        if (++contador >= periodo)
        {
            count--;
            countBCD = toBcd(count);

            if (count == 0){
                count = 19;
            }

            contador = 0;
        }



        IFS1bits.AD1IF == 0;
    }
    
}
