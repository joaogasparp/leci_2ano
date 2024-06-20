// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// PORTx é usado para ler nos portos configurados com saída
// LATx é usado para escrever nos portos configurados com entrada

#include <detpic32.h>

void send2displays(unsigned char value);

int main(void){
    LATB = (LATB & 0x80FF);         // 1000 0000 1111 1111
    LATD = (LATD & 0xFF9F);         // 1111 1111 1001 1111

    TRISB = (TRISB & 0x80FF);       // 1000 0000 1111 1111
    TRISD = (TRISD & 0xFF9F);       // 1111 1111 1001 1111

    while(1){
        send2displays(0x15);
        resetCoreTimer();
        while(readCoreTimer() < 20000 * 200);
    }
    return 0;
}

void send2displays(unsigned char value)
{
    static const char disp7scodes[] = {0x3F,0x06,0x5B,
        0x4F,0x66,0x6D,
        0x7C,0x07,0x7F,
        0x67,0x5F,0x7C,
        0x39,0x5E,0x79,0x71};

    LATDbits.LATD6 = !LATDbits.LATD6;
    LATDbits.LATD5 = !LATDbits.LATD5;

    if(LATDbits.LATD6 == 1)
    {
        LATB = (LATB & 0x80FF) | (disp7scodes[(value & 0xF0) >> 4] << 8);
    }else
    {
        LATB = (LATB & 0x80FF) | (disp7scodes[(value & 0x0F)] << 8);
    }
}
