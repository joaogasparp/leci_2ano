#include <detpic32.h>

int main(void) {

    int ns = 4;
    
    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected 
    AD1PCFGbits.PCFG4 = 0;      // RB4 configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this 
                                // mode an internal counter ends sampling and 
                                // starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time 
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = ns-1;
    
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;         // Enable A/D converter
    
    // Configure the A/D module and port RB4 as analog input 
    while(1) {
        double media = 0;
        double V;
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0);// Wait while conversion not done (AD1IF == 0)
        int *p = (int *)(&ADC1BUF0);
        int i;
        printf("\r");
        for( i = 0; i < ns; i++ ) {
            media += p[i*4];
        }
        media = media/ns;
        V=(media*33+511)/1023;
        printf("Volts : %.1f   %f",V/10, media);
        IFS1bits.AD1IF = 0; // Reset AD1IF         
    }
    return 0;
	
}
