#include <detpic32.h>

int main(void) {

    TRISBbits.TRISB4 = 1;       //RB4 desativar a porta de output digital
    AD1PCFGbits.PCFG4= 0;       //RB4 configured as analog input

    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this 
                                // mode an internal counter ends sampling and 
                                // starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time 
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 1-1;     //Interrupt is generated after 1 samples
                                //(replace XX by the desired number of
                                //consecutive samples) -> 1
                                
    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;         // Enable A/D converter
    
    // Configure the A/D module and port RB4 as analog input 
    while(1) {
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0);// Wait while conversion not done (AD1IF == 0)
        printInt(ADC1BUF0, 16 | 3 << 16);// Read conversion result (ADC1BUF0 value) and print it 
        printStr("\r");
        IFS1bits.AD1IF = 0; // Reset AD1IF          
    }
 
    return 0;
}
