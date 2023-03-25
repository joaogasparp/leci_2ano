# include <detpic32.h>

void send2displays(unsigned char value);
void delay (int ms);

int main(void){
    TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;// por os displays como outputs

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

    int freq;
    while (1)
    {
        int count =20;
        int i;
        do
        {
                    AD1CON1bits.ASAM = 1;               // Start conversion
                    while ( IFS1bits.AD1IF == 0 );      // Wait while conversion not done
                    i=0;
                    freq=(1+(ADC1BUF0/255));
                    do{
                        send2displays(count);
                        delay(20);  //50 hz
                    }while(++i<(1000/freq)/20);   //so pa explicar
                                                  //20 000 000 / 20 000 = 1000 
                                                  // 1000/ freq = freqtotal 
                                                  // e o resto safas te 
                                                  // eu penso assim :)
                    count--;
        } while (count>0);    //    20 000 000-1s                                  atualiza fr 50hz diminu o count a uma freq 5hz   20 000 000 / 20 000=
                                //     x - 1/50 20 ms ->50hz 200ms ->5hz

        IFS1bits.AD1IF = 0;                     // Reset AD1IF
    }

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
