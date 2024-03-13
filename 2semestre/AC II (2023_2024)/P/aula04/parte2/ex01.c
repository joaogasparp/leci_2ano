// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// PORTx é usado para ler nos portos configurados com saída
// LATx é usado para escrever nos portos configurados com entrada

#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    LATB = (LATB & 0x80FF);         // 1000 0000 1111 1111
    LATD = (LATD & 0xFF9F);         // 1111 1111 1001 1111

    TRISB = (TRISB & 0x80FF);       // 1000 0000 1111 1111
    TRISD = (TRISD & 0xFF9F);       // 1111 1111 1001 1111

    LATD = LATD | 0x0060;           // 0000 0000 0110 0000

    while(1)
    {
        char c = getChar();
        if (c == 'a' || c == 'A') LATB = (LATB & 0x80FF) | 0x0100;
        else if (c == 'b' || c == 'B') LATB = (LATB & 0x80FF) | 0x0200;
        else if (c == 'c' || c == 'C') LATB = (LATB & 0x80FF) | 0x0400;
        else if (c == 'd' || c == 'D') LATB = (LATB & 0x80FF) | 0x0800;
        else if (c == 'e' || c == 'E') LATB = (LATB & 0x80FF) | 0x1000;
        else if (c == 'f' || c == 'F') LATB = (LATB & 0x80FF) | 0x2000;
        else if (c == 'g' || c == 'G') LATB = (LATB & 0x80FF) | 0x4000;
        else LATB = (LATB & 0x80FF);
    }

    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000);
}
