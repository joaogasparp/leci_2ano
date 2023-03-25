#include <detpic32.h>

int main(void)
{
    // Configure Timer T3 (2 Hz with interrupts disabled)
                                // valor máximo de PRx = 2^16 - 1 = 65536

                                //k_prescaler = 20 000 000 / (65535+1) * fout(neste caso 2Hz) ) = 152 (aproximando ao mais alto é 256)
    T3CONbits.TCKPS = 7;        // 1:k_prescaler -> 1:256 -> 111 = 7 (PAG10 TIMERS manual);  
                                //fout_presc = 20 000 000 / 256 = 78125 > 65536;
                                //than calculate using this nect thing
    PR3 = 39063;                // Fout = 20Mhz / (256 * (39063 + 1)) = 1,999Hz          
    TMR3 = 0;                   // Reset timer T3 count register
    T3CONbits.TON = 1;          // Enable timer T3   

    while(1){
        // Wait while T3IF = 0
        while(IFS0bits.T3IF != 1);
        // Reset T3IF
        IFS0bits.T3IF = 0;

        putChar('.');
    }
    return 0;
}
