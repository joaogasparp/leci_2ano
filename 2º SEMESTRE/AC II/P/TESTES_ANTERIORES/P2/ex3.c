#include <detpic32.h>

void delay(int ms) {    
    for(; ms > 0; ms--){       
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    } 
}

void config_ADC(){
	TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
	AD1PCFGbits.PCFG4= 0; // RBx configured as analog input (AN4)
	AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
							// mode an internal counter ends sampling and
							// starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
							// interrupt is generated. At the same time,
							// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns) //tempo de amostragem
	AD1CON2bits.SMPI = 1 -1; // Interrupt is generated after XX samples
							// (replace XX by the desired number of
							// consecutive samples)
	AD1CHSbits.CH0SA = 4; // replace x by the desired input
							// analog channel (0 to 15)
	AD1CON1bits.ON = 1; // Enable A/D converter
						// This must the last command of the A/D
						// configuration sequence
}

void send2displays(int value,int base,int ms){
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
	
	// Select display low
	LATDbits.LATD6 = 0; // display high deactive
	LATDbits.LATD5 = 1; // display low active

	int low_d = value%base;
	
	LATB = (LATB & 0x80FF) | (display7Scodes[low_d] << 8);
	
	delay(ms/2);
	
	// Select display high
	LATDbits.LATD6 = 1; // display high active
	LATDbits.LATD5 = 0; // display low deactive

	int high_d = (int) value/base;
	
	LATB = (LATB & 0x80FF) | (display7Scodes[high_d] << 8);
	
	delay(ms/2);
	
 } 

int main(){
	
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;// por os displays como outputs
	
	config_ADC();
	
	while(1){
		
		int count=20;
		
		do{
			AD1CON1bits.ASAM=1;//start conversion
		
			while(IFS1bits.AD1IF==0);// espera até que a conversão termine
			
			int freq=1+(ADC1BUF0/255);		
			int ms=50/freq; // 50hz pq é a taxa de update do display 
							// como ja temos esse delay na linha 80 (20ms)
							// temos de contar com esse atraso
			count--;
			
			int i=0;
			for(;i<=ms;i++){//fica aqui os x ms 
				send2displays(count,10,20);
			}
			
			IFS1bits.AD1IF=0;//desativar a interrupção	
		}while(count!=0);

	}
	
	return 0;
}

