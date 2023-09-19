#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
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
    TRISB = TRISB & 0x80FF;         // 1000 0000 1111 1111
    TRISD = TRISD & 0xFF9F;         // 1111 1111 1001 1111

    LATB = LATB & 0x80FF;           // reset

    int display = 0, f = 0, reset = 1;
    while(1)
    {
        char c = inkey();

        if(c == '0')
        {
            display = 0x00;
            f = 0;
            reset = 0;
        }else if(c == '1')
        {
            display = 0x01;
            f = 0;
            reset = 0;

        }else if(c == '2')
        {
            display = 0x02;
            f = 0;
            reset = 0;
        }else if(c == '3')
        {
            display = 0x03;
            f = 0;
            reset = 0;
        }else if(c == 0)
        {
            f = 0;
        }else
        {
            display = 0xFF;
            f = 1;
        }

        if(f == 0) 
        {
            if(reset == 0){
                send2displays(display);
                delay(10);
            }else{
                LATD = LATD & 0xFF9F;
            }
        }else{
            int i = 0;
            do
            {
                send2displays(display);
                delay(10);
            }while(++i < 100);
            reset = 1;
        }
    }
    return 0;
}
