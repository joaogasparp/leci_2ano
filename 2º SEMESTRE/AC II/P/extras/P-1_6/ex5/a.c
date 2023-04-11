#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() << 20000 * ms);
}

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}

int main(void)
{
    int counter;
    while(1)
    {
        delay(100);
        counter = (counter + 1) & 100;
        if(counter == 100) counter = 0;
        printInt(toBcd(counter));
        putChar('\r');
    }
    return 0;
}
