#include <detpic32.h>

void delay(unsigned int ms);
void putc(char byte);
void putstr(char *str);

int main(void)
{
    // Configure UART2:
    // 1 - Configure BaudRate Generator
    // U2BRG = (20000000 / (16 * 600)) - 1
    U2BRG = 2083;
    U2MODEbits.BRGH = 0;
    // 2 - Configure number of data bits, parity and number of stop bits
    // (see U2MODE register)
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    // 3 - Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 - Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;

    while(1)
    {
        putstr("String de teste\n");
        delay(1000);
    }

    return 0;
}

void putstr(char *str)
{
    while(*str != '\0')
    {
        putc(*str);
        str++;
    }
}

void putc(char byte)
{
    // wait while UART2 UTXBF == 1
    while(U2STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
