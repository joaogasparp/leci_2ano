#include <detpic32.h>

volatile int adc_value;

int main(void)
{
    TRISE = TRISE & 0xFFFE;     // RE0 as output
    TRISD = TRISD & 0xF7FF;
    
    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0;      // RB4 configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;       // Conversion trigger constant
    AD1CON1bits.CLRASAM = 1;    // Stop conversion when the 1st A/D converter intetupr is generated.
                                // At the same time, hardware clears ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = 0;       // Interrupt is generated after 1 sample
    AD1CHSbits.CH0SA = 4;       // analog channel input 4
    AD1CON1bits.ON = 1;         // Enable the A/d configuration sequence

    // Enable interrupts ADC
    IPC6bits.AD1IP = 2;         // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;         // clear A/D interrupt flag
    IEC1bits.AD1IE = 1;         // enable A/D interrupts
    
    EnableInterrupts();

    AD1CON1bits.ASAM = 1;       // Start conversion

    while (1) { }
       
    return 0;
}

void _int_(27) isr_adc(void) {
    volatile int adc_value;
    // Reset RD11 (LATD11 = 0)
    LATDbits.LATD11 = 0;
    // Read ADC1BUF0 value to "adc_value"
    adc_value = ADC1BUF0;
    // Start A/D conversion
    AD1CON1bits.ASAM = 1;  
    // Set RD11 (LATD11 = 1)
    LATDbits.LATD11 = 1;
    // Reset AD1IF flag
    IFS1bits.AD1IF = 0; 
 } 
