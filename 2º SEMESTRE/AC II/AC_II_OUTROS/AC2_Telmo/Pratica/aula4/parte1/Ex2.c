#include <detpic32.h>

void delay(int ms);

int main(void)
{
    //reset
    LATE = (LATE & 0xFFF0);
    // Configure ports
    TRISE = (TRISE & 0xFFF0);

    int count = 0;
    
    while(1){
        LATE = count;
        // Wait 0.5s
        delay(500);
        // counter
        count = (count + 1) & 0x000F;
    } 
return 0;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}