#include <detpic32.h>

void putstr(char *s);
void putc(char byte);

int main(void){
	
	//REset
	LATE = (LATE & 0xFFEF) | 0x0010;
	
	//port
	TRISB = TRISB | 0x000F;
	TRISE = TRISE & 0xFFEF;
	
	//UART2
	U2BRG= 129;
	U2MODEbits.BRGH = 0;

	U2MODEbits.PDSEL = 2;
	U2MODEbits.STSEL = 1;
	
	U2STAbits.UTXEN = 1;
	U2STAbits.UTXEN = 1;
	
	U2MODEbits.ON = 1;
	
	//UART2 INTERRUPT
	IEC1bits.U2RXIE = 1;
	IEC1bits.U2TXIE = 0;
	IPC8bits.U2IP = 2;
	IFS1bits.U2RXIF = 0;
	
	U2STAbits.URXISEL = 0;
	

	EnableInterrupts();

	while(1);
	
	return 0;
}	
void _int_ (32) isr_uart2 (void){

	if(IFS1bits.U2RXIF == 1){
		char byte = U2RXREG;
		
		if(byte == 'p'){
			putstr("DipSwitch=");
			putc(PORTBbits.RB3 + 0x30);
			putc(PORTBbits.RB2 + 0x30);
			putc(PORTBbits.RB1 + 0x30);
			putc(PORTBbits.RB0 + 0x30);
		}
		
		if(byte == 't')
			LATE = LATE ^ 0x0010;
		
		IFS1bits.U2RXIF = 0;
	}
}

void putc(char byte){
	// wait while UTXBF == 1
	while(U2STAbits.UTXBF == 1);
	// Copy byte2send to the UxTXREG register
	U2TXREG = byte;
}

void putstr(char *s){

	while(*s != '\0'){
		putc(*s);
		s++;
	}
	
}


