#include <detpic32.h>

int main(void) {
    
    T3CONbits.TCKPS = 7;        // K_prescaler = 20 000 000 / ((65535+1) * fout (neste caso 2Hz)) = 152 (aproximando ao mais alto é 256)
                                // 1:K_prescaler -> 1:256 -> 111 = 7 (PAG10 TIMERS manual);  
    PR3 = 39062;                // 2Hz = (20 000 000 / 256) / (PR2 + 1) <=> PR2 = 39 062        
    TMR3 = 0;                   // Clear timer T3 count register
    T3CONbits.TON = 1;          // Enable timer T3 (must be the last command of the timer configuration sequence)

    while(1) {
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;
        putChar('.');
    }

    return 0;
}