#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    LATBbits.LATB8 = 0;
    TRISBbits.TRISB8 = 0;
    LATBbits.LATB9 = 0;
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB10 = 0;
    TRISBbits.TRISB10 = 0;
    LATBbits.LATB11 = 0;
    TRISBbits.TRISB11 = 0;
    LATBbits.LATB12 = 0;
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 0;
    LATBbits.LATB14 = 0;
    TRISBbits.TRISB14 = 0;
    LATDbits.LATD5 = 0;
    TRISDbits.TRISD5 = 0;
    LATDbits.LATD6 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    ATDbits.LATD6 = 0;

    while(1)
    {
        char c = getChar();
        if((c >= 'a' || c <= 'g') && (c >= 'A' || c <= 'G'))
        {
            switch(c)
            {
                case 'a':
                case 'A':
                    LATB = 
                    break;
                
            }
        }

        
    }
    
}