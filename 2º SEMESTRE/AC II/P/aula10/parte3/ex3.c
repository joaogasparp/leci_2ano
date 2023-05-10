#include <detpic32.h>

void delay(unsigned int ms);
void putc(char byte);
void putstr(char *str);

int main(void)
{
    // Configure UART2 (19200, N, 8, 1)
    U2BRG = 65;
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    LATDbits.LATD = 0xF7FF;
    TRISDbits.TRISD = 0xF7FF;

    while(1)
    {
        // Set RD11
        LATD = LATD | 0x0800;
        putstr("12345");
        // Reset RD11
        LATD = LATD & 0xF7FF;
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
