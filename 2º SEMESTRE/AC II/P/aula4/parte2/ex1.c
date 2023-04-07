#include <detpic32.h>

int main(void)
{
    LATB = (LATB & 0x80FF);      // 1000 0000 1111 1111
    LATD = (LATD & 0xFF9F);      // 1111 1111 1001 1111

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1)
    {
        char c = getChar();
        switch(c)
        {
            case 'a':
            case 'A':
                LATB = 0x0100;
                break;
            case 'b':
            case 'B':
                LATB = 0x0200;
                break;
            case 'c':
            case 'C':
                LATB = 0x0400;
                break;
            case 'd':
            case 'D':
                LATB = 0x0800;
                break;
            case 'e':
            case 'E':
                LATB = 0x1000;
                break;
            case 'f':
            case 'F':
                LATB = 0x2000;
                break;
            case 'g':
            case 'G':
                LATB = 0x4000;
                break;
            default:
                break;            
        }
    }
    return 0;    
}
