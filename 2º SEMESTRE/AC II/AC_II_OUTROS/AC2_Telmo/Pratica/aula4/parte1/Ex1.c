#include <detpic32.h>

void delay(int ms);

int main(void)
{
    //reset
    LATCbits.LATC14 = 0;
    // Configure port RC14 as output
    TRISCbits.TRISC14 = 0;
    
    while(1){
        // Wait 0.5s
        delay(500);
        // Toggle RC14 port value
        LATCbits.LATC14 = !LATCbits.LATC14;
    }
return 0;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}