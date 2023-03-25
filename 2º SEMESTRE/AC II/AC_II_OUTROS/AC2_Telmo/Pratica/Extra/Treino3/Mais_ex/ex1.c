#include <detpic32.h>

void config_T2();
void delay(int ms);
void config_PWM();
void setPWM(unsigned int dutyCycle);

int main(){

    config_T2();
    config_PWM();

    TRISB = TRISB | 0x0009;
    TRISE = TRISE & 0xFFFE;

    LATEbits.LATE0 = 0;//!TESTAR LED 

    while(1){

        int val = PORTB & 0x0009;
        if(val==1){//25%
            setPWM(25);
        }else if(val==8){//70%
            setPWM(70);
        }

        LATEbits.LATE0 = PORTDbits.RD1;//! testar led

        delay(250);//250us
    }


}

void config_T2(){
	// Kprescaler = (20 000 000)/((65535+1)*Fout);
	// Kprescaler -> escolher a constante + perto arredondada para cima
	// Fout_prescale= 20 000 000/Kprescaler;
	// PRx= (Fout_prescale/Fout)-1;

	// Configure Timer Tx
    T2CONbits.TCKPS = 1;// Tipo A Prescalar: 1, 8, 64 ou 256
                      // Tipo B Prescalar: 1, 2, 4, 8, 16, 32, 64 ou 256
    PR2 = 35714;// PRx                            
    TMR2 = 0; // Reset timer Tx count register           
    T2CONbits.TON = 1;// Enable timer Tx (must be the last command of the timer configuration sequence) 
}


void delay(int ms) {
  for(; ms > 0; ms--) {
    resetCoreTimer();
    while(readCoreTimer() < 20);
  }
}

void config_PWM(){
	OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL = 0;// a=0 -> using T2, a=1 -> using T3
    OC2RS = 0; // Ton constant -- pode ser apagado é dado pelo setPWM
    OC2CONbits.ON = 1; // Enable OC1 module
}

void setPWM(unsigned int dutyCycle){ // PWM do Timer3
    if(dutyCycle>=0 & dutyCycle<=100){ OC2RS = ((PR2+1)*dutyCycle)/100; }// para outros timers basta mudar o PRx
} 
