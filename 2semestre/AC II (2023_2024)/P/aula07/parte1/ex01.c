#include <detpic32.h>

// Interrupt Handler
void _int_(27) isr_adc(void) {
    // Read conversion result (ADC1BUF0) and print it
    read = ADC1BUF0;
    // Start A/D conversion
    AD1CON1bits.ASAM = 1;
    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;
}

int main(void) {
    // Configure all (digital I/O, analog input, A/D module)
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // Configure interrupt system
    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    // Global Interrupt Enable
    EnableInterrupts();

    // Start A/D conversion
    AD1CON1bits.ASAM = 1;

    // all activity is done by ISR
    while(1);

    return 0;
}