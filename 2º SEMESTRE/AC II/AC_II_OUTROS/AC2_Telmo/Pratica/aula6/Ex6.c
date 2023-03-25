#include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

int main(void){
	 TRISBbits.TRISB4 = 1; // RBx digital output disconnected
	 AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
	 AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	 // mode an internal counter ends sampling and
	 // starts conversion
	 AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	 // interrupt is generated. At the same time,
	 // hardware clears the ASAM bit
	 AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	 AD1CON2bits.SMPI = 4-1; // Interrupt is generated after XX samples
	 // (replace XX by the desired number of
	 // consecutive samples)
	 AD1CHSbits.CH0SA = 4; // replace x by the desired input
	 // analog channel (0 to 15)
	 AD1CON1bits.ON = 1; // Enable A/D converter
	 // This must the last command of the A/D
	 // configuration sequence 
	 
	 //reset
    	LATB = (LATB & 0x80FF);
    	LATD = (LATD & 0xFF9F);
	 
	TRISB = (TRISB & 0x80FF) | 0xF;	// Defenir [RB8 - RB14] como saidas
    TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas
    	
    	int i = 0;
    	char v = 0;
	 
	while(1){
	if(i==0){
		double media = 0;
		AD1CON1bits.ASAM = 1;
		while( IFS1bits.AD1IF == 0);
		int *p = (int *)(&ADC1BUF0);
		for( i = 0; i < 4; i++ ) {
			media += (double)p[i*4];
		}
		media = media / 4;
		v = (media * 33 + 511) / 1023;
		IFS1bits.AD1IF = 0;
		}
		send2displays(toBcd(v));
		delay(10); //100hz
		i = (i + 1) % 20; 	//10 * 20 * 5 vezez * 20000 = 20000000 = 1 s 
	}
	
	return 0;

}


//funcao send2displays
void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
                                    //   0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F   
    static char displayFlag = 0; // static variable: doesn't loose its
                                // value between calls to function
    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;
    // if "displayFlag" is 0 then send digit_low to display_low
    if(!displayFlag){
        LATD = (LATD & 0xFF9F) | 0x0020;
        digit_low = display7Scodes[digit_low];
        LATB = (LATB & 0x80FF ) | digit_low << 8;
    }
    // else send digit_high to didplay_high
    else{
        LATD = (LATD & 0xFF9F) | 0x0040;
        digit_high = display7Scodes[digit_high];
        LATB = (LATB & 0x80FF ) | digit_high << 8;
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}

unsigned char toBcd(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
} 

