#include <detpic32.h>

void delay(unsigned int ms);
void send2displays(unsigned int val, int flag);

int main(void) {

    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    LATEbits.LATE1 = 1;
    TRISEbits.TRISE1 = 0;
    LATEbits.LATE1 = 0;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 2-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    while(1){
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);

        LATEbits.LATE1 = !LATEbits.LATE1;

        int i;
        int soma = 0, media = 0;
        int *p = (int *)(&ADC1BUF0);
        for( i = 0; i < 2; i++ )
        {
            soma += p[i*4];
        }
        media = soma / 2;
        
        int valorEscala = (media * 0x9 - 0x0) / 1023 + 0x0;
        send2displays(valorEscala, 0);
        
        printInt(media, 16 | 3 << 16);
        putChar('\n');

        delay(1000/6);

        IFS1bits.AD1IF = 0;
    }

    return 0;
}

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void send2displays(unsigned int val, int flag) {

    int static segments[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                            0x7F,0x6F,0x77,0x7C,0x39,0xE5,0x79,0x71};

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
