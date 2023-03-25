#include <detpic32.h>

void delay(int ms);

int main(void){
    
    //reset
    LATD = (LATD & 0xFF9F);
    LATB = (LATB & 0x80FF);
    // Configure ports
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    //configure dysplay
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1){
        char c = getChar();
        switch (c){
        case 'a':
        case 'A':
            LATB =   0x0100;   // RB8 = 1
            break;
        case 'b':
        case 'B':
            LATB =   0x0200;   // RB9 = 1
            break;
        case 'c':
        case 'C':
            LATB =   0x0400;   // RB10 = 1
            break;
        case 'd':
        case 'D':
            LATB =   0x0800;   // RB11 = 1
            break;
        case 'e':
        case 'E':
            LATB =   0x1000;   // RB12  = 1
            break;
        case 'f':
        case 'F':
            LATB =   0x2000;   // RB13 = 1
            break;
        case 'g':
        case 'G':
            LATB =   0x4000;   // RB14 = 1
            break;
        default:
            break;
        }
    
    }
    return 0;
}