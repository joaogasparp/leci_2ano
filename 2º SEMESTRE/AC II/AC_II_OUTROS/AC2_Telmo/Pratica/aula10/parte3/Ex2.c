#include <detpic32.h>

void putstr(char *str);
void putc(char byte);
void delay(int ms);

int main(void)
{
    // Configure UART2 (19200, N, 8, 1)
    // 1 - Configure BaudRate Generator
    U2BRG = 64;     //BaudRate = 19200 ->(20000000 / (16 * 19200)) - 1 = 10
    U2MODEbits.BRGH = 0;
    // 2 – Configure number of data bits, parity and number of stop bits(see U2MODE register)
    U2MODEbits.PDSEL = 0;   //00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;   //0 = 1 Stop bit
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;

    // config RD11 as output
    LATD = LATD & 0xF7FF;
    TRISD = TRISD & 0xF7FF;

    while(1){
        // Wait while TRMT == 0
        while(U2STAbits.TRMT == 0);
        // Set RD11
        LATD = LATD | 0x0800;
        putstr("12345");
        //putstr("123456789AB");
        LATD = LATD & 0xF7FF;
    }

    return 0;
}

void putstr(char *str){
    while (*str != '\0'){
        putc(*str); 
        str++;
    }
    
}

void putc(char byte) {
    while(U2STAbits.UTXBF == 1);// wait while UART2 UTXBF == 1
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}


