#include <detpic32.h>

int main(void)
{
    //ports
    TRISE = TRISE & 0xFFF5;                 // RE3 to RD1 as output   0101   1010
    LATE = (LATE & 0xFFF5) | 0x000A;        //reset
    
    // Configure Timers T1 and T3 with interrupts enabled)
    T3CONbits.TCKPS = 4;        
    PR3 = 49999;                         
    TMR3 = 0;                   
    T3CONbits.TON = 1;


    T1CONbits.TCKPS = 6;        
    PR1 = 62499;                         
    TMR1 = 0;                   
    T1CONbits.TON = 1;

    // Reset T1IF and T3IF flags and enable interrupts
    IPC3bits.T3IP = 2;      // Interrupt priority 1
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 

    IPC1bits.T1IP = 1;      // Interrupt priority 1
    IEC0bits.T1IE = 1;      // Enable timer T1 interrupts
    IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag 
    

    //Perguntar ao sor se trocar as prioridades n muda e n entendo pq que n interessa
    EnableInterrupts();         // Global Interrupt Enable
    while(1);
    return 0;
}


void _int_(4) isr_T1(void){
    // toggle RD0
    LATE = LATE ^ 0x0002; 
    // Reset T1IF flag
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    // toggle RD2
    LATE = LATE ^ 0x0008; 
    // Reset T3IF flag  
    IFS0bits.T3IF = 0; 
}
