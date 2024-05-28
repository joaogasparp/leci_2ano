#include <detpic32.h>

void putc(char byte2send);
void putStr(char *string);

volatile int count;

int main(void)
{
    TRISE = TRISE & 0xFFE1;
    LATE = (LATE & 0xFFE1) | (count << 1);

    U2BRG = 130; // ((20000000 + 8 * 9600) / (16 * 9600)) - 1 = 130
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U3TXIE = 0;
    IPC8bits.U2IP = 2;
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 0;

    EnableInterrupts();

    count = 15;

    while (1)
        ;

    return 0;
}

void _int_(32) isr_uart2(void)
{
    if (IFS1bits.U2RXIF == 1)
    {
        // Read character from FIFO (U2RXREG)
        char a;
        a = U2RXREG;
        if (a == 'U')
        {
            count++;
            if (count == 16)
            {
                count = 0;
            }
        }
        else if (a == 'R')
        {
            count = 0;
            putStr("RESET");
        }
        LATE = (LATE & 0xFFE1) | (count << 1);
        IFS1bits.U2RXIF = 0;
    }
}

void putc(char byte2send)
{
    while (U2STAbits.UTXBF == 1)
        ;
    U2RXREG = byte2send;
}

void putStr(char *string)
{
    while (*string != '\0')
    {
        putc(*string++);
    }
}
