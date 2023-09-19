#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    TRISE = TRISE & 0xFF80;         // 1111 1111 1000 0000
    LATE = LATE & 0xFF80;           // reset

    int counter = 0;

    while(1){
        counter = (counter + 1) % 60;
        if(counter > 60) counter = 0;
        delay(1000);
        LATE = (LATE & 0xFF87) | counter;
    }
}
