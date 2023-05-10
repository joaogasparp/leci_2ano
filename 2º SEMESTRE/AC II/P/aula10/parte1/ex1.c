#include <detpic32.h>

// BaudRate = 115200 bps
// Sem paridade
// 8 data bits
// 1 stop bit
// Divisão do relógio de 16

int main(void)
{
    // Configure UART2:
    // 1 - Configure BaudRate Generator
    // U2BRG = (20000000 / (16 * 115200)) - 1
    U2BRG = 10;
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

    return 0;
}
