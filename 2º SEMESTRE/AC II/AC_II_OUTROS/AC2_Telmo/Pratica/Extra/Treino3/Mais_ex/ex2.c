#include <detpic32.h>

void send2displays(unsigned int value,unsigned int base);
void configADC(int numSamples);
void config_T2();
void configInterrupts_TimerT2();
void delay(int ms);

volatile int temperature=0;

int main(){
    configADC(2);
    config_T2();
    configInterrupts_TimerT2();

    LATB = (LATB & 0x80FF);
    TRISB = (TRISB & 0x80FF);  
    TRISDbits.TRISD5=0;
    TRISDbits.TRISD6=0;

    EnableInterrupts();

    while(1){
        AD1CON1bits.ASAM = 1; // Start conversion
        while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done (AD1IF == 0)

        int *p = (int *)(&ADC1BUF0);
        int i = 0;
        int soma = 0;
        for(; i < 2; i++ ){ // pode nao ser 8 depende do nº de samples
            soma = p[i*4] + soma;	
        } 
        int media = soma/2; // pode nao ser 8 depende do nº de samples	
        temperature=((media*45 +)/1023)+20;

        delay(100);//10hz
    }
}

void send2displays(unsigned int value,unsigned int base){
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};							
	static char displayFlag = 0;	
	
	if( displayFlag == 0){	//display_low
        int tmp = value % base;
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;		
		LATB = ( LATB & 0x80FF ) | (display7Scodes[tmp] << 8 );	
	}else{	// display_high
        int tmp = value / base;
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;	
		LATB = ( LATB & 0x80FF ) | (display7Scodes[tmp] << 8 );
	}
	
	displayFlag = !displayFlag;// toggle "displayFlag"
}

void configADC(int numSamples) {
  TRISBbits.TRISB4 = 1;	
  AD1PCFGbits.PCFG4 = 0;
  AD1CHSbits.CH0SA = 4;	
  AD1CON2bits.SMPI = numSamples - 1;
  AD1CON1bits.SSRC = 7;
  AD1CON1bits.CLRASAM = 1;
  AD1CON3bits.SAMC = 16;
  AD1CON1bits.ON = 1;
}

void delay(int ms) {
  for(; ms > 0; ms--) {
    resetCoreTimer();
    while(readCoreTimer() < 20000);
  }
}

void config_T2(){
	// Kprescaler = (20 000 000)/((65535+1)*Fout);
	// Kprescaler -> escolher a constante + perto arredondada para cima
	// Fout_prescale= 20 000 000/Kprescaler;
	// PRx= (Fout_prescale/Fout)-1;

	// Configure Timer Tx
    T2CONbits.TCKPS = 2;// Tipo A Prescalar: 1, 8, 64 ou 256
                      // Tipo B Prescalar: 1, 2, 4, 8, 16, 32, 64 ou 256
    PR2 = 41666;// PRx                            
    TMR2 = 0; // Reset timer Tx count register           
    T2CONbits.TON = 1;// Enable timer Tx (must be the last command of the timer configuration sequence) 
}

void configInterrupts_TimerT2(){
    IPC2bits.T2IP = 2; // interrupt priority
    IEC0bits.T2IE = 1; // Enable Tx interrupts
    IFS0bits.T2IF = 0; // clear interrupt flag	
}

void _int_(8) isr_T2(void){ // T1=4 | T2=8 | T3=12  
	// do stufs
    send2displays(temperature,10);
    // Reset TxIF flag consoante o Tx
    IFS0bits.T2IF=0;
}
