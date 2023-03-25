#include <detpic32.h>

int main(void)
{
    
    // Configure Timer T3 with interrupts enabled
    T3CONbits.TCKPS = 7;
    PR3 = 39063;
    TMR3 = 0;                   // Reset timer T3 count register 
    T3CONbits.TON = 1;          // Enable timer T3   
    
    // Configure interrupt system
    IPC3bits.T3IP = 1;      // Interrupt priority 1
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 

    EnableInterrupts();

    while (1);
        
    return 0;
}

void _int_(12) isr_T3(void){        // vector T3 = 12

    putChar('.');
    // Reset T3 interrupt flag
    IFS0bits.T3IF = 0;
}
