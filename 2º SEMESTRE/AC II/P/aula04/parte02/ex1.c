#include <detpic32.h>

int main(void)
{
    LATD = (LATD & 0xFF9F);
    LATB = (LATB & 0x80FF);

    TRISD = (TRISD & 0xFF9F);
    TRISB = (TRISB & 0x80FF);

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1)
    {
        char c = getChar();
        switch(c)
        {
            case 'a':
            case 'A':
                LATB = 0x7700;
                break;
            case 'b':
            case 'B':
                LATB = 0x7C00;
                break;
            case 'c':
            case 'C':
                LATB = 0x3900;
                break;
            case 'd':
            case 'D':
                LATB = 0x5E00;
                break;
            case 'e':
            case 'E':
                LATB = 0x7900;
                break;
            case 'f':
            case 'F':
                LATB = 0x7100;
                break;
            default:
                break;            
        }
    }
    return 0;    
}