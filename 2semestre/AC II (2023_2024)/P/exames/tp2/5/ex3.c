#include <detpic32.h>

void configUART(){
    U2MODEbits.BRGH = 0;
    U2BRG = 129;
    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IPC8bits.U2IP = 2;
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
    IFS1bits.U2EIF = 0;
    EnableInterrupts();
}

void putc(char c){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = c;
}

void puts(char *str){
    while(*str){
        putc(*str++);
    }
}

char getc(void){
    if(U2STAbits.OERR == 1){
        U2STAbits.OERR = 0;
    }
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}

volatile int count = 0;

int main(void){
    configUART();
    TRISE = TRISE & 0xFF7F;
    TRISB = TRISB & 0x0009;
    while(1);

    return 0;
}

void _int_(32) uart(void){
    if(IFS1bits.U2RXIF){
        char c;
        c = U2RXREG;
        putc(c); 
        puts("\n");
        if(c == 'D'){
            PORTEbits.RB7 != PORTEbits.RB7;
            puts("SDS=\n");
        }
    }
    IFS1bits.U2RXIF = 0;
}

// 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
//  0     1    2    3    4    5    6    7    8   9    A    B    C     D    E    F

//RE7
//1111 1111 0111 1111   0xFF7F

//RB3 a 0
//0000 0000 0000 1001   0x0009