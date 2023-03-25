#include <detpic32.h>

void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);
void delay(int ms);

volatile unsigned char voltage = 0;     // Global variable
int smp = 8;                            //number of samples

int main(void){
    unsigned int cnt = 0;

    // Configure all (digital I/O, analog input, A/D module, interrupts)
    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0;      // RB4 configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;       // Conversion trigger constant
    AD1CON1bits.CLRASAM = 1;    // Stop conversion when the 1st A/D converter intetupr is generated.
                                // At the same time, hardware clears ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = smp-1;       // Interrupt is generated after xx sample
    AD1CHSbits.CH0SA = 4;       // analog channel input 4
    AD1CON1bits.ON = 1;         // Enable the A/d configuration sequence

    // Configure interrupt system
    IPC6bits.AD1IP = 2;         // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;         // clear A/D interrupt flag
    IEC1bits.AD1IE = 1;         // enable A/D interrupts

    // Configure displays
    TRISB = TRISB & 0x80FF;         // RB14 to RB8 as output
    TRISD = TRISD & 0xFF9F;         // Displays high/low as output

    EnableInterrupts();             // Global Interrupt Enable
    
    // Start A/D conversion
    AD1CON1bits.ASAM = 1; 
    
    while(1)
    {
        if(cnt == 0)                    // 0, 200 ms, 400 ms, ... (5 samples/second)
        {
            // Start A/D conversion
            AD1CON1bits.ASAM = 1; 
        }

        // Send "voltage" value to displays
        send2displays(voltage);
        
        cnt = (cnt + 1) % 20;
        // Wait 10 ms
        delay(10);
    }

    return 0;
}

void _int_(27) isr_adc(void){

    // Calculate buffer average (8 samples)
    int *p = (int *) &ADC1BUF0;
    int average = 0;
    int i;
    for ( i = 0; i < smp; i++){
        average += p[i * 4];
    }
    
    average = average / smp;
    // Calculate voltage amplitude
    voltage = (average * 33 + 511) / 1023;
    // Convert voltage amplitude to decimal and store the result in the global variable "voltage"
    voltage = toBcd(voltage);
    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;
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

unsigned char toBcd(unsigned char value){
	return ((value / 10) << 4) + (value % 10);
} 

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}
