// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// PORTx é usado para ler nos portos configurados com saída
// LATx é usado para escrever nos portos configurados com entrada

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
        delay(370);
        count = (count + 9) % 10;
    }
    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
