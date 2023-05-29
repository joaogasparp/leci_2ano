#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void _int_(27) isr_adc(void)
{
    volatile int adc_value;
    LATDbits.LATD11 = 0;
    adc_value = ADC1BUF0;
    LATDbits.LATD11 = 1;
    AD1CON1bits.ASAM = 1;       // Start A/D conversion
    IFS1bits.AD1IF = 0;         // Reset AD1IF flag de interrupção de ADC
}

int main(void)
{
    TRISDbits.TRISD11 = 0;
    
    // Configure all:
    // digital I/O
    TRISBbits.TRISB4 = 1;

    // analog input
    AD1PCFGbits.PCFG4 = 0;

    // A/D module
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
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

    // all activity is done by the ISR
    while(1)
    {
    }
    return 0;
}
