#include <detpic32.h>

void delay(unsigned int ms);
void putc1(char byte);

int main(void)
{
    // Configure UART2 (19200, N, 8, 2)
    U2BRG = 65;
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 1;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;
    
    while(1)
    {
        putc1(0x0F);
        delay(10);
    }

    return 0;
}

void putc1(char byte)
{
    // wait while UART2 UTXBF == 1
    while(U1STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U1TXREG = byte;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
