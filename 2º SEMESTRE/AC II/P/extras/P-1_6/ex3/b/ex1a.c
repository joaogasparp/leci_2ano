#include <detpic32.h>

int main(void)
{
    TRISB = (TRISB | 0x000F);       // RB como input
    TRISE = (TRISE & 0xFFF0);       // RE como output

    while (1)
    {
        LATE = (LATE & 0xFFF0) | (PORTB & 0x000F);
    }
    return 0;
}