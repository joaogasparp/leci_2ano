#include <detpic32.h>

void putc(char byte);

int main(void)
{
    // Configure UART2: 115200, N, 8, 1
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    // Configure UART2 interrupts, with RX interrupts enabled
    // and TX interrupts disabled:
    // enable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    // set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 1;
    // clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    // define RX interrupt mode (URXISEL bits)
    U2STAbits.URXISEL = 0;

    // Enable global interrupts
    EnableInterrupts();

    while(1);
    return 0;
}

void _int_(32) isr_uart2(void)
{
    if(IFS1bits.U2RXIF == 1)
    {
        // Read character from FIFO (U2RXREG)
        char a = U2RXREG;
        // Send the character using putc()
        putc(a);
        // Clear UART2 Rx interrupt flag
        IFS1bits.U2RXIF = 0;
    }
}

void putc(char byte)
{
    // wait while UART2 UTXBF == 1
    while(U2STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}
