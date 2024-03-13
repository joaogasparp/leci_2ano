#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    LATE = (LATE & 0xFF87);
    TRISE = (TRISE & 0xFF87);
    int count = 0;

    while(1)
    {
        LATE = (LATE & 0xFF87) | (count << 3);
        delay(250);
        count = (count + 1) % 10;
    }
    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
