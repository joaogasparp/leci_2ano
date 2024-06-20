#include <detpic32.h>

void delay(unsigned int ms);
void putc1(char byte);

int main(void)
{
    // Configure UART2 (115200, N, 8, 1)
    U1BRG = 10;
    U1MODEbits.BRGH = 0;

    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    
    U1MODEbits.ON = 1;
    
    while(1)
    {
        putc1(0x5A);
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
