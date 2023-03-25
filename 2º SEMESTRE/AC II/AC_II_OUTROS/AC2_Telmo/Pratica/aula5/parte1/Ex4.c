#include <detpic32.h>

void send2displays(unsigned char value);
void delay(int ms);

int main (void){
    //reset
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    // Configure ports
    TRISB = (TRISB & 0x80FF);   //out
    TRISD = (TRISD & 0xFF9F);   //out

    while(1){
    send2displays(0x15);
    // wait 0.2s
    //delay(200);
    // wait 20Hz
    //delay(50);
    // wait 50Hz
    //delay(20);
    // wait 100Hz
    delay(1);
    }

}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
                                    //   0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F   
    static char displayFlag = 0; // static variable: doesn't loose its
                                // value between calls to function
    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;
    // if "displayFlag" is 0 then send digit_low to display_low
    if(!displayFlag){
        LATD = (LATD & 0xFF9F) | 0x0020;
        digit_low = display7Scodes[digit_low];
        LATB = (LATB & 0x80FF ) | digit_low << 8;
    }
    // else send digit_high to didplay_high
    else{
        LATD = (LATD & 0xFF9F) | 0x0040;
        digit_high = display7Scodes[digit_high];
        LATB = (LATB & 0x80FF ) | digit_high << 8;
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}