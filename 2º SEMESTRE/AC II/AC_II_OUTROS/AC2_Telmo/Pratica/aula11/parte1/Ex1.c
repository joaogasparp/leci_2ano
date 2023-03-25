#include <detpic32.h>

int main(void)
{
    // Configure UART2: 115200, N, 8, 1
    // 1 - Configure BaudRate Generator
    U2BRG = 10;     //BaudRate = 115200 ->(20000000 / (16 * 115200)) - 1 = 10
    U2MODEbits.BRGH = 0;
    // 2 – Configure number of data bits, parity and number of stop bits(see U2MODE register)
    U2MODEbits.PDSEL = 0;   //00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;   //0 = 1 Stop bit
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;

    // Configure UART2 interrupts, with RX interrupts enabled and TX interrupts disabled:
    //enable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0; 
    //set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 1;
    //clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    //define RX interrupt mode (URXISEL bits)
    U2STAbits.URXISEL=0;        //has 1 character
    // Enable global Interrupts
    EnableInterrupts();
    while(1);

    return 0;

}