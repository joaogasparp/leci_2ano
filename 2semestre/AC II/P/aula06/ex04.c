// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// PORTx é usado para ler nos portos configurados com saída
// LATx é usado para escrever nos portos configurados com entrada

#include <detpic32.h>

int main(void){
    TRISBbits.TRISB4 = 1;

    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    while(1){
        AD1CON1bits.ASAM = 1;
        while( IFS1bits.AD1IF == 0 );

        int i;
        int *p = (int *)(&ADC1BUF0);
        for( i = 0; i < 16; i++ )
        {
            printInt( p[i*4], 10 | 4 << 16 );
            putChar(' ');
        }
        putChar('\r');

        IFS1bits.AD1IF = 0;
    }
    
    return 0;
}
