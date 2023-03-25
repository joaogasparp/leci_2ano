#include <detpic32.h>

void delay(int ms);

int main(void){
    int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
                        //   0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F    

    //reset
    LATD = (LATD & 0xFF9F);
    LATB = (LATB & 0x80FF);
    // Configure ports
    TRISB = (TRISB | 0x000F);   //in
    TRISB = (TRISB & 0x80FF);   //out
    TRISD = (TRISD & 0xFF9F);   //out

    //configure dysplay
    LATD = (LATD | 0x0040);     //RD6 = 1

    while(1){
        // read dip-switch
        int index = PORTB & 0x000F;
        // convert to 7 segments code
        int num = display7Scodes[index];
        // send to display
        LATB= num << 8;
    }
    return 0;
}
