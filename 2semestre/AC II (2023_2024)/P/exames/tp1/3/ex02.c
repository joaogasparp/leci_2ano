#include <detpic32.h>

void send2displays(unsigned int val);
void delay(unsigned int ms);

int main(void) {
    LATE = LATE & 0xFF80; // resetar rb7 a rb0  -> para os leds
    LATB = LATB & 0xFFFC; // resetar rb1 a rb0  -> para os leds
    LATB = LATB & 0x80FF; // resetar rb15 a rb8 -> para os displays
    LATD = LATD & 0xFF9F; // resetar rd6 a rd5  -> para os displays

    TRISE = TRISE & 0xFF80; // configurar como saída rb7 a rb0
    TRISB = TRISB & 0xFFF3; // configurar como entrada rb1 a rb0
    TRISB = TRISB & 0x80FF; // configurar como saída rb15 a rb8
    TRISD = TRISD & 0xFF9F; // configurar como saída rd6 a rd5

    int count = 0, i = 0, num = 0;
    char tecla;

    while(1) {
        LATE = (LATE & 0xFF80) | count;
        delay(200);
        if(++count>60) count = 0;
        tecla = inkey();

        switch(PORTB & 0x0003) {
            case 0:
                LATD = LATD & 0xFF9F;
                break;
            case 1:
                if(tecla <= '9' && tecla >= '1') {
                    num = tecla;
                }
                for(i = 0; i < 10; i++) {
                    num = num & 0x0F;
                    send2displays(num);
                    delay(20);
                }
                break;
            case 2:
                if(tecla <= '9' && tecla >= '1') {
                    num = tecla << 4;
                }
                for(i = 0; i < 10; i++) {
                    num = num & 0xF0;
                    send2displays(num);
                    delay(20);
                }
                break;
            case 3:
                i = 0;
                for(i = 0; i < 10; i++) {
                    send2displays(count);
                    delay(20);
                }
                break;
        }
    }
    return 0;
}

void send2displays(unsigned int val) {

    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    int static flag = 0;

    int digitLow = val % 16;
    int digitHigh = val / 16;

    if(flag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[digitLow] << 8);
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[digitHigh] << 8);
    }
    flag = !flag;
}

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
