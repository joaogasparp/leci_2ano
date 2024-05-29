#include <detpic32.h>

void delay(unsigned int us){
    resetCoreTimer();
    while(readCoreTimer()<20 * us);
}

void setDutyCycle(unsigned int dc){
    OC3RS = ((PR3 + 1) * dc) / 100;
}

int main(void){
    TRISB = TRISB | 0x0003;

    T3CONbits.TCKPS = 2;
    PR3 = 38461;
    TMR3 = 0;
    T3CONbits.TON = 1;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL =0;
    setDutyCycle(50);
    OC1CONbits.ON = 1;
    
    while(1){
        if(PORTBbits.RB1 == 1 && PORTBbits.RB0 == ){
            setDutyCycle(25);
        }
        else if(PORTBbits.RB2 ==  && PORTBbits.RB0 == ){
            setDutyCycle(75);
        }
        delay(360);
    }

    return 0;
}

// 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
//  0     1    2    3    4    5    6    7    8   9    A    B    C     D    E    F

//RB2 e RB0
//0000 0000 0000 0011       0x0003

//Prescaler = 20000000 / (130*65536) = 2.34750601
//Prescaler = 4 => 2
//PR3 = (20000000 / 4) / 130 = 38461.538461538