// Dar reset é apenas aos outputs
// TRISx é para definir com entrada (1) ou saída (0)
// LATx é para escrever num porto configurado como saída e dar reset
// PORTx é para ler num porto configurado como entrada
//

#include <detpic32.h>

void send2displays(unsigned char value)
{
    static const char disp7scodes[] = {0x3F,0x06,0x5B,
        0x4F,0x66,0x6D,
        0x7C,0x07,0x7F,
        0x67,0x5F,0x7C,
        0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;

    if(displayFlag == 0)                    // if "displayFlag" is 0 then send digit_low to display_low
    {
        LATB = (LATB & 0xFF9F) | 0x0020;    // dar reset
        digit_low = disp7scodes[digit_low];
        LATB = (LATB & 0X80FF) | (digit_low << 8);
    }else                                   // select display low
    {
        LATB = (LATB & 0x80FF) | 0x0040;    // dar reset
        digit_high = disp7scodes[digit_high];
        LATB = (LATB & 0X80FF) | (digit_high << 8);
    }

    displayFlag = ! displayFlag;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    LATB = (LATB & 0x80FF);             // reset do RB8 a RB14
    LATD = (LATD & 0xFF9F);             // reset do RD5 a RD6

    TRISB = (TRISB & 0x80FF);           // configure RB8-RB14 as outputs
    TRISD = (TRISD & 0xFF9F);           // configure RD5-RD6 as outputs

    int counter = 0;

    while(1)
    {
        int i = 0;
        do
        {
            send2displays(counter);
            delay(10);
        } while(++i < 20);              // como 100Hz são 10ms e 5Hz são 200ms temos que 10ms*20=200ms
        counter = (counter + 1) & 256;
    }
    return 0;
}
