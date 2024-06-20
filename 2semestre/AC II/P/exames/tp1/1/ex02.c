#include <detpic32.h>

void send2displays(unsigned int val);
void delay(unsigned int ms);

int main(void) {

    LATB = (LATB & 0x80FF);         // resetar a posição dos displays 
    LATD = (LATD & 0xFF9F);         // resetar ao display mais e menos significativo
    LATB = (LATB & 0xFFFD);         // resetar o rb1
    LATEbits.LATE4 = 1;             // resetar o re4

    TRISB = (TRISB & 0x80FF);       // configurar os displays como saída
    TRISD = (TRISD & 0xFF9F);       // configurar os displays como saída
    TRISB = (TRISB & 0x0002);       // configurar o rb1 como entrada
    TRISEbits.TRISE4 = 0;           // configurar o re4 como saída

    LATEbits.LATE4 = 0;

    // configurar o ADC
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    while(1) {
        AD1CON1bits.ASAM = 1;
        while( IFS1bits.AD1IF == 0 );

        LATEbits.LATE4 = !LATEbits.LATE4;

        int i;
        int *p = (int *)(&ADC1BUF0);        
        int soma = 0, media = 0;
        for( i = 0; i < 4; i++ )
        {
            soma += p[i*4];
        }
        media = soma / 4;

        int valorEscala = (media * (0xC - 0x3)) / 1023 + 0x3;
        int rb1 = PORTBbits.RB1;

        if (rb1 == 0) {
            send2displays(valorEscala);
        } else {
            send2displays(valorEscala << 4);
        }

        printInt(media, 2 | 10 << 16);
        putChar('\n');

        delay(20);
    }

    return 0;
}

void send2displays(unsigned int val) {

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

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
