#include <detpic32.h>

void send2displays(unsigned int val);
void delay(unsigned int ms);
unsigned char toBcd(unsigned char value);

// Global variable
volatile unsigned char voltage = 0;

void _int_(27) isr_adc(void) {
    int average, amplitude;

    // Read 8 samples (ADC1BUF0, ..., ADC1BUF7) and calculate average
    average = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8;
    // Calculate voltage amplitude
    amplitude = (average * 33 + 511) / 1023;
    // Convert voltage amplitude to decimal and store the result in the global variable "voltage"
    voltage = toBcd(amplitude);
    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;
}

int main(void) {
    unsigned int cnt = 0;

    // Configure all (digital I/O, analog input, A/D module, interrupts)
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 8-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // Global Interrupt Enable
    EnableInterrupts();

    while(1) {
        if(cnt == 0) {
            // Start A/D conversion
            AD1CON1bits.ASAM = 1;
        }
        // Send "voltage" value to displays
        send2displays(voltage);
        cnt = (cnt + 1) % 10;
        delay(1000);
    }

    return 0;
}

void send2displays(unsigned int val) {

    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0xE5,0x79,0x71};
    int static flag = 0;

    int digitLow = val % 16;
    int digitHigh = val / 16;

    if(flag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[digitLow] << 8);
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[digitHigh] << 8);
    }
    flag = !flag;
}

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}
