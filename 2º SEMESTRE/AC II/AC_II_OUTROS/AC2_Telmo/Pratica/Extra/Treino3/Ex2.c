#include <detpic32.h>

int samp = 2;
int voltage = 0;
void delay(int ms);
void send(unsigned char value);
unsigned char toBcd(unsigned char num);

int main(void){
	
	//Port
	LATD = LATD & 0xFF9F;
	LATB = LATB & 0x80FF;
	
	//port
	TRISD = TRISD & 0xFF9F;
	TRISB = TRISB & 0x80FF;
	
	//ADC
	TRISBbits.TRISB2 = 1;
	AD1PCFGbits.PCFG2 = 0;
	AD1CON1bits.SSRC = 7;
	
	AD1CON1bits.CLRASAM = 1;
	
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = samp-1;
	
	AD1CHSbits.CH0SA = 4;
	
	AD1CON1bits.ON = 1;

	//TIMER
	T2CONbits.TCKPS = 2;
	PR2 = 41665;
	TMR2 = 0;
	T2CONbits.TON = 1;
	
	//TIMER INTERRUPCOES
	IPC2bits.T2IP = 2;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;
	
	EnableInterrupts();
	
	while(1){
		AD1CON1bits.ASAM = 1;
		while( IFS1bits.AD1IF == 0 );
		int *p = (int *)(&ADC1BUF0);
		int i;
		int average = 0;
		for(i = 0; i < samp ; i++){
			average += p[i * 4];
		}
		average = average/samp;
		voltage = ((average * 45 + 511)/1023) + 20;
		delay(2000000);
		IFS1bits.AD1IF = 0;
	
	}
}

void _int_(8) isr_T2 (void){
	send(toBcd(voltage));
	IFS0bits.T2IF = 0;
}

void send(unsigned char value){
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



void delay(int ms){
	resetCoreTimer();
	while(readCoreTimer() < ms);
}

unsigned char toBcd(unsigned char num){
	return ((num /10) << 4) + (num % 10);
}
