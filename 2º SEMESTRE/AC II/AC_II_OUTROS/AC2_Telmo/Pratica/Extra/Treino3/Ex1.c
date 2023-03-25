#include <detpic32.h>

volatile int duty = 1;
void delay(int ms);
void set(int num);

int main(void){
	
	//port
	TRISB = TRISB | 0x0009;
	
	//TIMER
	T2CONbits.TCKPS = 1;
	PR2 = 35713;
	TMR2 = 0;
	T2CONbits.TON = 1;	
	
	//OC2
	OC2CONbits.OCM = 6;
	OC2CONbits.OCTSEL =0;
	OC2RS = ((PR2 +1) * duty )/100;
	OC2CONbits.ON = 1;
	
	while(1){
		if((PORTB & 0x0009) == 0x0001)
			set(25);
		if((PORTB & 0x0009) == 0x0008)
			set(70);
		
		delay(5000);		//250us
	}
	
}
void delay(int ms){
	resetCoreTimer();
	while(readCoreTimer() < ms);
}

void set(unsigned int num){
	if(duty >= 0 && duty <= 100)
		OC2RS = ((PR2 +1) * duty )/100;
}
