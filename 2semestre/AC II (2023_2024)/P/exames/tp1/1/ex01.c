// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// para configurar como saída tem de ser colocado a 0
// PORTx é usado para ler nos portos configurados como entrada
// LATx é usado para escrever nos portos configurados como saída


#include <detpic32.h>

int main(void) {

    int freq = 7.3;

    int state = 0xC0;               // 1100 0000

    LATE = (LATE & 0xFF03);         // 1111 1111 0000 0011
    LATB = (LATB & 0xFFFA);         // 1111 1111 1111 1010

    TRISE = (TRISE & 0xFF03);       // saída
    TRISB = (TRISB & 0x0005);       // entrada 0000 0000 0000 0101

    while(1) {
        int rb2 = PORTBbits.RB2;
        int rb0 = PORTBbits.RB0;

        if(rb2 == 0 && rb0 == 0) {
            freq = 4.6;
        } else if(rb2 == 1 && rb0 == 1) {
            freq = 7.3;
        }

        LATE = (LATE & 0xFF03) | state;
        state = state >> 1;

        resetCoreTimer();
        while(readCoreTimer() < 20000 * (1000/freq));

        if(state < 0x0C){           // 0000 1100
            state = 0xC0;
        }
    }

    return 0;
}
