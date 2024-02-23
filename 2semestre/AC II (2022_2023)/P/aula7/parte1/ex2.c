#include <detpic32.h>

volatile unsigned char voltage = 0; // Global variable

volatile int average, amplitude;

void _int_(27) isr_adc(void)
{
    average = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8;      // Read 8 samples (ADC1BUF0, ..., ADC1BUF7) and calculate average
    amplitude = average * 1023 / 23;    // Calculate voltage amplitude
                                        // Convert voltage amplitude to decimal and store the result in the global variable "voltage"
    IFS1bits.AD1IF = 0;                 // Reset AD1IF flag
}

void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x5F, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // Lista de caracteres

    if(LATDbits.LATD6 == 1)
    {
        LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0xF0) >> 4] << 8);
    } else
    {
        LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0x0F)] << 8);
    }
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    unsigned int cnt = 0;

    // Configure all (digital I/O, analog input, A/D module, interrupts)
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;
    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    TRISD = (TRISD & 0xFF9F);
    TRISB = (TRISB & 0x80FF);

    // Global Interrupt Enable
    EnableInterrupts();

    while(1)
    {
        if(cnt == 0) // 0, 200 ms, 400 ms, ... (5 samples/second)
        {
            AD1CON1bits.ASAM = 1;   // Start A/D conversion
        }
        send2displays(((voltage/10)*16)+(voltage%10));
        cnt = (cnt + 1) % 10;
        delay(1000);
    }
    return 0;
}
