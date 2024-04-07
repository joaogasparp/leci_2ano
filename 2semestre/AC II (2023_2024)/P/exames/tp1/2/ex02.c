#include <detpic32.h>

void send2displays(unsigned int val);
void delay(unsigned int ms);

int main(void) {

    LATB = LATB & 0x80FF;
    LATD = LATD & 0xFF9F;       // 1111 1111 1001 1111

    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    char tecla, teclaAnt = 0;
    int i;

    while(1) {
        tecla = inkey();

        if(tecla != 0) {
            teclaAnt = tecla;
        }

        if(teclaAnt != -1) {
            if(teclaAnt == '0') {
                send2displays(0x00);
            } else if(teclaAnt == '1') {
                send2displays(0x01);
            } else if(teclaAnt == '2') {
                send2displays(0x02);
            } else if(teclaAnt == '3') {
                send2displays(0x03);
            } else {
                teclaAnt = -1;
                for(i = 0; i < 100; i++) {
                    send2displays(0xFF);
                    delay(10);
                }   // 100 Hz da frequência de atualização são 10 ms no entanto
                // queremos que esteja ativo durante 1 segundo e por isso,
                // 10 ms * x = 1000 ms -> x = 100
                LATB = LATB & 0x80FF;
            }
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
