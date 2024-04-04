// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// PORTx é usado para ler nos portos configurados com saída
// LATx é usado para escrever nos portos configurados com entrada
// 1/Hz = segundos * 1000 = milisegundos

#include <detpic32.h>

void send2displays(unsigned int val);

int main(void){
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    while(1){
        send2displays(0x15);
        resetCoreTimer();
        // while(readCoreTimer() < 20000 * (1/20*1000));       // 50 ms
        // while(readCoreTimer() < 20000 * (1/50*1000));       // 20 ms
        while(readCoreTimer() < 20000 * (1/100*1000));      // 10 ms
    }
    return 0;
}

void send2displays(unsigned int val){

    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0xE5,0x79,0x71};
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