// TRISx é usado para configurar os portos com entrada ou saída
// para configurar como entrada tem de ser colocado a 1
// PORTx é usado para ler nos portos configurados com saída
// LATx é usado para escrever nos portos configurados com entrada
// 1/Hz = segundos * 1000 = milisegundos
// frequência de atualização do contador/incremento é tudo, a frequência de refrescamento 
// é o do delay

#include <detpic32.h>

void send2displays(unsigned int val);
unsigned char toBcd(unsigned char value);

int main(void){
    unsigned int counter, displayCounter;

    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    LATE = (LATE & 0xFF00);

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    TRISE = (TRISE & 0xFF00);
    TRISB = (TRISB | 0x0001);

    counter = 0;

    while(1)
    {
        if (PORTBbits.RB0 == 1){
            if (counter % 50 == 0 && counter != 0){
                    displayCounter++;
                if (displayCounter >= 60){
                    displayCounter = 0;
                    }
                }
            }else {
                if (counter % 50 == 0 && counter != 0){
                    displayCounter--;
                    if (displayCounter < 0){
                        displayCounter = 59;
                    }
                }
            }
            send2displays(counter);
            LATE = (LATE & 0xFF00) | toBcd(displayCounter);
            counter++;
            resetCoreTimer();
            while(readCoreTimer() < 20000 * 10);
    }
    return 0;
}

void send2displays(unsigned int val){

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

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}