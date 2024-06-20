#include <detpic32.h>

void putc(char byte2send);
void putstr(char *str);

int main(void)
{
    TRISE = TRISE & 0xFF7F; 
    TRISB = TRISB & 0x000F;

    U2BRG = 130; // ((20000000 + 8 * 9600) / (16 * 9600)) - 1
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    // enable
    IEC1bits.U2RXIE = 1;
    // priority
    IPC8bits.U2IP = 2;
    // flags
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
    IFS1bits.U2EIF = 0;

    EnableInterrupts();

    while (1)
        ;

    return 0;
}

void putc(char byte2send)
{
    while (U2STAbits.UTXBF == 1)
        ;                // wait while UTXBF == 1
    U2TXREG = byte2send; // Copy byte2send to the UxTXREG register
}

void putstr(char *str)
{
    while (*str)
    {
        putc(*str++);
    }
}

void _int_(32) isr_uart(void)
{
    if (IFS1bits.U2RXIF)
    {
        char c;
        c = U2RXREG;
        LATEbits.LATE7 = !LATEbits.LATE7;

        if (c == 'D')
        {
            putstr("DSD=");
            int switches = PORTB & 0x000F;
            if (switches > 9)
            {
                putc('1');
                putc((switches % 10) + '0');
            }
            else
            {
                putc(switches + '0');
            }
            putc('\n');
        }
    }
    IFS1bits.U2RXIF = 0;
}
