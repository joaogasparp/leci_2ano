#include <detpic32.h>

int main(void)
{
    LATE = (LATE & 0xFFF0);         // reset a RE

    TRISB = (TRISB | 0x000F);       // RB como input
    TRISE = (TRISE & 0xFF00);       // RE como output

    while (1)
    {
        LATEbits.LATE0 = PORTBbits.RB3;
        LATEbits.LATE1 = PORTBbits.RB2;
        LATEbits.LATE2 = PORTBbits.RB1;
        LATEbits.LATE3 = PORTBbits.RB0;
    }
    return 0;
}