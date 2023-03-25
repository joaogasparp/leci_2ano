#include <detpic32.h>

void delay(int ms);
void putc(char byte);

int main(void){
    // Configure UART1 (115200, N, 8, 1)
    // 1 - Configure BaudRate Generator
    U1BRG = 10;         //BaudRate = 115200 ->(20000000 / (16 * 115200)) - 1 = 10
    U1MODEbits.BRGH = 0;
    // 2 – Configure number of data bits, parity and number of stop bits(see U2MODE register)
    U1MODEbits.PDSEL = 0;   //00 = 8-bit data, no parity
    U1MODEbits.STSEL = 0;   //0 = 1 Stop bit
    // 3 – Enable the trasmitter and receiver modules (see register U1STA)
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    // 4 – Enable UART2 (see register U1MODE)
    U1MODEbits.ON = 1;

    while(1)
    {
    putc(0x5A);
    // wait 1 s
    delay(1);
    }
    return 0;
}

void putc(char byte){
    // wait while UART2 UTXBF == 1
    while(U1STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U1TXREG = byte;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}
