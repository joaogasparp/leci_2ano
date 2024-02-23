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

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned int val){

    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0xE5,0x79,0x71};
    int static flag = 0;

    int digitLow = val % 16;
    int digitHigh = val / 16;

    if(flag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[digitLow] << 8);
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[digitHigh] << 8);
    }
    flag = !flag;
}

int main(void)
{
    LATB = (LATB & 0x80FF);             // reset do RB8 a RB14
    LATD = (LATD & 0xFF9F);             // reset do RD5 a RD6
    LATE = (LATE & 0xFF00);             // reset do RE0 a RE7
    LATC = (LATC & 0xBFFF);             // reset do RC14

    TRISB = (TRISB & 0x80FF);           // configure RB8-RB14 as outputs
    TRISD = (TRISD & 0xFF9F);           // configure RD5-RD6 as outputs
    TRISE = (TRISE & 0xFF00);           // configure RE0-RE7 as outputs
    TRISB = (TRISB | 0x0001);           // configura RB0 as input
    TRISC = (TRISC & 0xBFFF);           // configure RC14 as output

    int counter = 0;

    while(1)
    {
        int i = 0;
        if((PORTB & 0x0001) == 1)
        {  
            do
            {
                send2displays(counter);
                LATE = (LATE & 0xFF00) | toBcd(counter);
                delay(10);
            } while(++i < 20);              // como 100Hz são 10ms e 5Hz são 200ms temos que 10ms*20=200ms
            counter = (counter + 1) & 60;
        } else
        {
            do
            {
                send2displays(counter);
                LATE = (LATE & 0xFF00) | toBcd(counter);
                delay(10);
            } while(++i < 20);
            counter = (counter - 1) & 60;
        }
        if(counter > 59)
        {
            counter = 0;
            LATC = LATC & 0x4000;
            delay(5000);
            LATC = LATC & 0xBFFF;
        }
        if(counter < 0){
            counter = 60;
            LATC = LATC & 0x4000;
            delay(5000);
            LATC = LATC & 0xBFFF;
        }
    }
    return 0;
}
