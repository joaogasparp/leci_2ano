#include <detpic32.h>

void putc(char byte);
void putStr(char *str);

int count;

int main(void)
{
    TRISE = TRISE & 0xFFF0;
    LATE = (LATE & 0xFFF0) | (count << 1);

    U2BRG = 520;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 1;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 1;
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 0;

    EnableInterrupts();

    while (1)
        ;

    return 0;
}

void putc(char byte)
{
    while (U2STAbits.UTXBF == 1)
        ;
    U2TXREG = byte;
}

void putStr(char *str)
{
    while (*str != '\0')
        putc(*str++);
}

void _int_(32) isr_U2RX(void)
{
    if (IFS1bits.U2RXIF == 1)
    {
        char c;
        c = U2RXREG;
        if (c == 'F')
        {
            count++;
            if (count == 9)
            {
                count = 0;
            }
        }
        else if (c == 'C')
        {
            count = 0;
            putStr("VALOR MINIMO");
        }
        LATE = (LATE & 0xFFF0) | (count << 1);
        IFS1bits.U2RXIF = 0;
    }
}
