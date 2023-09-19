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
    int counter=0;
    while(1)
    {
        int c = inkey();
        int incr;

        double freq = 2*(1+c);

        if(freq == 0)
        {
            incr = 0;
        }else
        {
            incr = 1000/freq;
        }

        printInt(toBcd(counter));
        delay(incr);
        putChar('\r');

        counter = (counter + 1) & 100;
        if(counter == 100) counter = 0;        
    }
    return 0;
}
