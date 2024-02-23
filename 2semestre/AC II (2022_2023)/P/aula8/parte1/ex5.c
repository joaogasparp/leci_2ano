#include <detpic32.h>

int main(void)
{
    // Configure Timers T1 and T3 with interrupts enabled
    // T1
    T1CONbits.TCKPS = 6;
    PR1 = 62499;
    TMR1 = 0;
    T1CONbits.TON = 1;
    // T3
    T3CONbits.TCKPS = 4;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;
    // Reset T1IF and T3IF flags
    // T1
    IPC1bits.T1IP = 1;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    // T3
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD2 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD2 = 0;

    EnableInterrupts(); // Global Interrupt Enable
    while(1);
    return 0;
}

void _int_(4) isr_T1(void)
{
    LATDbits.LATD0 = !LATDbits.LATD0;
    // Reset T1IF flag
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void)
{
    LATDbits.LATD2 = !LATDbits.LATD2;
    // Reset T3IF flag  
    IFS0bits.T3IF = 0; 
}
