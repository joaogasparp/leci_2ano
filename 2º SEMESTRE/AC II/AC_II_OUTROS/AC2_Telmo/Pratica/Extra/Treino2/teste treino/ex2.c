#include <detpic32.h>

void delay(int ms) {    
    for(; ms > 0; ms--){       
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    } 
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
	
	TRISB = TRISB & 0x80FF;// RB8-RB14 output
	TRISD = TRISD & 0xFF9F;// RD5-RD6 output

	char c;
	char c_ant;
	while(1){
	
		c = inkey();
		
		if(c!=0){
			c_ant=c;
		}
		
		if(c_ant!=-1){
			if(c_ant=='0'){
				send2displays(0,10,10);
			}else if(c_ant=='1'){
				send2displays(1,10,10);
			}else if(c_ant=='2'){
				send2displays(2,10,10);
			}else if(c_ant=='3'){
				send2displays(3,10,10);
			}else{
				c_ant=-1;
				int i=0;
				for(;i<100;i++){// 1 segundo
					send2displays(255,16,10);
				}
				LATB = LATB & 0x80FF;
			}
		}

	}

	return 0;
}


