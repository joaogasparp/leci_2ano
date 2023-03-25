#include <detpic32.h>



int main(void){
    
    //Ports
    TRISD = TRISD | 0x0100;
    TRISE = TRISE & 0xFFFE;

    // Reset T1IF flags and enable interrupts
    IPC1bits.INT1IP = 2;      // Interrupt priority INT1
    IEC0bits.INT1IE = 1;      // Enable timer INT1 interrupts
    IFS0bits.INT1IF = 0;      // Reset timer INT1 interrupt flag


    // Configure Timers T1 with interrupts enabled)  //2hz/ 2 = 1hz/3 = 0.3hz 
    T2CONbits.TCKPS = 7;        
    PR2 = 39063;                              
    TMR2 = 0;                   
    T2CONbits.TON = 1;


    // INT1 config
    INTCONbits.INT1EP = 0;

    EnableInterrupts();         // Global Interrupt Enable

    while (1);

    return 0;
}

void _int_ (8) isr_T2 (void){
    static int count = 0;

    LATE = (LATE & 0xFFFE) | 0x0001;

    count = count + 1;

    if(count % 6 == 0){
        IEC0bits.T2IE = 0;      // Enable timer T2 interrupts
        LATE = (LATE & 0xFFFE); //turns of led
        putChar('c');
    }
    
    //resets times 2hz in 2hz
    IFS0bits.T2IF = 0;
    
}


void _int_ (7) isr_INT1 (void){
    IPC2bits.T2IP = 1;      // Interrupt priority 1
    IEC0bits.T2IE = 1;      // Enable timer T2 interrupts
    IFS0bits.T2IF = 0;      // Reset timer T2 interrupt flag
    putChar('b');

    //waits for another push on int1
    IFS0bits.INT1IF = 0;
}

