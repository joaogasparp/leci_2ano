#include <detpic32.h>

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
    static char displayFlag = 0; // static variable: doesn't loose its value between calls to function
    int digit_low = value % 10;
    int digit_high = value / 10;
    // if "displayFlag" is 0 then send digit_low to display_low
    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_low] << 8));
    }
    // else send digit_high to didplay_high
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_high] << 8));
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}

int main(void){

    // Configuração dos portos RD e RB
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;


    TRISBbits.TRISB4 = 1;       // RBx digital output disconnected
    AD1PCFGbits.PCFG4 = 0;      // RBx configured as analog input
    
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this
                                // mode an internal counter ends sampling and
                                // starts conversion

    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time,
                                // hardware clears the ASAM bit

    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    
    AD1CON2bits.SMPI = 3;     // Interrupt is generated after N samples
                                // (replace N by the desired number of
                                // consecutive samples)

    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)

    AD1CON1bits.ON = 1;         // Enable A/D converter
                                // This must the last command of the A/D
                                // configuration sequence

    int i;
    while(1){
        // Start conversion
        AD1CON1bits.ASAM = 1;

        // Wait while conversion not done (AD1IF == 0)
        while( IFS1bits.AD1IF == 0 );

        // Read conversion result (ADC1BUF0 value) and print it
        int *p = (int *)(&ADC1BUF0);
        int som = 0;
        for( i = 0; i < 4; i++ ) {
            som += p[i*4];
        }
        float med = som / 4;
        int v = (med*33+511)/1023;
        
        // Display
        int t = 0;
        do{
            send2displays(v);

            // wait 10 ms (1/100Hz)
            delay(10);

        } while(++t < 20);      // 10 * 20 = 200ms 
        

        // Reset AD1IF
        IFS1bits.AD1IF = 0;
    }
    return 0;
}
