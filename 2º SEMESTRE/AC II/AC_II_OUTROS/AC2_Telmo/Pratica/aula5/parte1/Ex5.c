    #include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);

int main(void){
    // declare variables
    int i, counter;
    // initialize ports
    TRISD = TRISD & 0xFF9F;
    TRISB = TRISB & 0x80FF;

    counter = 0;
    while(1){
        i = 0;
        do{
            send2displays(counter);
            // wait 20 ms
            delay(20);
        } while(++i < 10);      //wait 5Hz = 10 * 20 = 200 ms
        // increment counter (mod 256)
        counter =( counter + 1 ) & 0x00FF;
    }
    return 0;
}

//funcao send2displays
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