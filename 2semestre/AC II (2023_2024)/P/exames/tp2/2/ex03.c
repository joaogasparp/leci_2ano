#include <detpic32.h>

volatile int count;

int main(void)
{
    count = 15;

    TRISE = TRISE & 0xFFE1; // 1111 1111 1110 0001
    LATE = LATE & 0xFFE1 | (count << 1);

    U2BRG = 130; // ((20000000 + (8 * 9600)) / (16 * 9600)) - 1 = 130
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;

    U2STAbits.UT2EN = 1;
    U2STAbits.UR2EN = 1;

    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IPC8bits.U2IP = 2;
    IFS1bits.UxRXIF = 0;
    IFS1bits.U2TXIF = 0;
    IFS1bits.U2EIF = 0;

    while (1)
        ;

    return 0;
}

void _int_(32) uart(void)
{
    if (IEC1bits.U2RXIE)
    {
        char c;
        c = U2RXREG;
        if(c == 'U')
        {
            if(count == 15) count = 0;
            count++;
        } else if (c == 'R')
        {
            count = 0;
            putstr("RESET\n");
        }
        LATE = LATE & 0xFFE1 | (count << 1);
        IEC1bits.U2RXIE = 0;
    }
}

void putc(char byte2send)
{
    // wait while UTXBF == 1
    while(U2STAbits.UTXBF == 1);
    // Copy byte2send to the UxTXREG register
    U2TXREG = byte2send;
}

void putstr(char *str)
{
    while(*str) putc(*str++);
}
