// Para configurar como entrada ou saída é com TRISx
// Para configurar como entrada (input) é com | e meter a 1
// Para configurar como saída (output) é com & e meter a 0
//

#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}


int main(void)
{
    TRISE = (TRISE & 0xFF03);           // configure RE2-RE7 as outputs
    TRISB = (TRISB | 0x0005);           // configura RB0 e RB2 as input

    LATE = (LATE & 0xFF03);             // reset do RE0 a RE7

    long double freq = 7.3;

    while(1)
    {
        if((PORTB & 0x0005) == 1)
        {
            freq = 7.3;
        }else{
            freq = 4.6;
        }

        LATE = LATE &
        
    }
    return 0;
}
