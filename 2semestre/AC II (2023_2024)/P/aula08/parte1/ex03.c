#include <detpic32.h>

int main(void) {

    T3CONbits.TCKPS = 7;
    PR3 = 39062;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 1;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    EnableInterrupts();
    while(1);
    return 0;
}

void _int_(12) isr_T3(void) {
    // 2Hz -> 0.5s
    // para ser 1Hz -> 1s, inicializa-se count a 0
    // e vai-se alternando entre 0 e 1. quando count == 0
    // imprime-se um ponto
    static int count = 0;
    count = (count + 1) % 2; 
    if(count == 0)
        putChar('.');

    IFS0bits.T3IF = 0;
}