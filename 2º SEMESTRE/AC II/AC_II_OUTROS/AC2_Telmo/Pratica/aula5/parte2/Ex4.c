
#include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

int main(void){
    // declare variables
    int counter, i , j,  refresh;
    //reset
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    LATE = (LATE & 0xFF00);
    // Configure ports
    TRISB = (TRISB | 0x000F);   //in
    TRISB = (TRISB & 0x80FF);   //out
    TRISD = (TRISD & 0xFF9F);   //out
    TRISE = (TRISE & 0xFF00);   //out

    counter = 0;
    refresh = 20; 
    while(1){
        i = 0;
        do{
            send2displays(toBcd(counter));
	        LATE = (LATE & 0xFF00) | toBcd(counter);
            delay(10);
        } while(++i < refresh);  
        // increment counter (mod 60)
        if((PORTB & 0x0001) == 0x0001 ){
            if(++counter > 59)
                counter = 0;
            if(counter == 59){
                j = 0;
                do{
                    i = 0; 
                    do{
                        send2displays(toBcd(counter));
                        LATE = (LATE & 0xFF00) | toBcd(counter);
                        delay(10);
                    }while(++i < 20);
                    LATD = LATD & 0xFF9F;
                    delay(200);
                }while(++j < 12.5);
            }
            refresh = 20;
        }
        else{
            if(--counter < 0)
                counter = 59;
            if(counter == 0){
                j = 0;
                do{
                    i = 0; 
                    do{
                        send2displays(toBcd(counter));
                        LATE = (LATE & 0xFF00) | toBcd(counter);
                        delay(10);
                    }while(++i < 50);
                    LATD = LATD & 0xFF9F;
                    delay(500);
                }while(++j < 5);
            }
            refresh = 50;
        }
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

unsigned char toBcd(unsigned char value){
return ((value / 10) << 4) + (value % 10);
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}
