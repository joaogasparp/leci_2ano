#include <detpic32.h>

int main(void)
{
    /// Configure Timer T2 and interrupts
    T2CONbits.TCKPS = 7;        
    PR2 = 39062;
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 1;        // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1;        // Enable timer T2 interrupts
    IFS0bits.T2IF = 0;        // Reset timer T2 interrupt flag

    // Configure ports and external interrupt INT1
    TRISDbits.TRISD8 = 1;
    IPC1bits.INT1IP = 2;      // Interrupt priority INT1
    IEC0bits.INT1IE = 1;      // Enable timer INT1 interrupts
    IFS0bits.INT1IF = 0;      // Reset timer INT1 interrupt flag


 
    EnableInterrupts();
    while(1);
    return 0;
}

void _int_(8) isr_T2(void)
{
    
}

void _int_(7) isr_INT1(void)
{

}
