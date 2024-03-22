#include <detpic32.h>

int main(void){
    volatile int aux;
    TRISDbits.TRISD11 = 0;

    // Configure A/D module; configure RD11 as a digital output port
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    while(1){
        AD1CON1bits.ASAM = 1;           // Start conversion
        LATDbits.LATD11 = 1;            // Set LATD11 (LATD11=1)
        while(IFS1bits.AD1IF == 0);     // Wait while conversion not done (AD1IF ==0 )
        LATDbits.LATD11 = 0;            // Reset LATD11 (LATD11=0)
        aux = ADC1BUF0;                 // Read conversion result (ADC1BUF0) to "aux" variable
        IFS1bits.AD1IF = 0;             // Reset AD1IF (should be done after reading the conversion result)
    }


    return 0;
}

// aux = 3.36 us (microseconds)
