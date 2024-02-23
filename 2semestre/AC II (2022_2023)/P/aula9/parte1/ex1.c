#include <detpic32.h>

volatile int voltage = 0;       // Global variable
double average = 0;

void configureAll()
{
    // digital I/O
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    // analog input e A/D module
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // timers T1 and T3
    T1CONbits.TCKPS = 2;
    PR1 = 62499;
    TMR1 = 0;
    T1CONbits.TON = 1;

    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T1CONbits.TON = 1;

    // interrupts
    IPC1bits.T1IP = 2;          // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1;          // Enable timer T1 interrupts
    IPC3bits.T3IP = 2;          // Interrupt priority 2
    IEC0bits.T3IE = 1;          // Enable timer T3 interrupts


}

void _int_(4) isr_T1(void)
{
    AD1CON1bits.ASAM = 1;       // Start A/D conversion
    IFS0bits.T1IF = 0;          //  Reset timer T1 interrupt flag
}

void _int_(12) isr_T3(void)
{
    send2displays(voltage);     // Send "voltage" value to displays (global variable)
    IFS0bits.T3IF = 0;          //  Reset timer T3 interrupt flag
}

void _int_(27) isr_adc(void)
{
    int i;
    int *p = (int *)(&ADC1BUF0);
    for(i = 0; i < 8; i++)
    {
        average += p[i*4];
    }
    average = average / 8;
    voltage = (average * 33 + 511) / 1023;
    putChar(toBcd(voltage));
    IFS1bits.AD1IF = 0;         // Reset AD1IF flag
}

unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
    static char displayFlag = 0;
    int digit_low = value % 10;
    int digit_high = value / 10;
    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_low] << 8));
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_high] << 8));
    }
    displayFlag = !displayFlag;
}

int main(void)
{
    configureAll();
    IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag
    IFS1bits.AD1IF = 0;     // Reset AD1IF
    EnableInterrupts();     // Global Interrupt Enable
    while(1);
    return 0;
}
