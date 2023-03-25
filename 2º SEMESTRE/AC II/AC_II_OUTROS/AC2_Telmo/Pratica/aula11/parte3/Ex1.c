#include <detpic32.h>


void configureAll();
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

int num = 8;
volatile int voltage = 0;
volatile int voltMin = 33;
volatile int voltMax = 0;

int main(void){
    
    configureAll();
    

    EnableInterrupts();  

	while(1);
	
	return 0;

}

void configureAll(){

    //reset
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
	
    //Ports
	TRISB = (TRISB & 0x80FF);	    // Defenir [RB8 - RB14] como saidas
    TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas


    // ADC
    TRISBbits.TRISB4 = 1;       // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;       // RBx configured as analog input
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this
                                // mode an internal counter ends sampling and
                                // starts conversion

    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time,
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = num-1;   // Interrupt is generated after XX samples
                                // (replace XX by the desired number of
                                // consecutive samples)
    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter
                                // This must the last command of the A/D
                                // configuration sequence 

    //Timers
    //T3 a 100
    T3CONbits.TCKPS = 2;        
    PR3 = 49999;                         
    TMR3 = 0;                   
    T3CONbits.TON = 1;

    //T1 a 5
    T1CONbits.TCKPS = 2;        
    PR1 = 62499;                         
    TMR1 = 0;                   
    T1CONbits.TON = 1;

    // Enable interrupts ADC, T1, T3
    IPC6bits.AD1IP = 3;     // configure priority of A/D interrupts
    IEC1bits.AD1IE = 1;     // Enable A/D interrupts
    IFS1bits.AD1IF = 0;     // Reset timer AD interrupt flag 
    
    IPC3bits.T3IP = 2;      // Interrupt priority 2
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 
    

    IPC1bits.T1IP = 1;      // Interrupt priority 1
    IEC0bits.T1IE = 1;      // Enable timer T1 interrupts
    IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag 
    
    // Configure UART2: 115200, N, 8, 1
    // 1 - Configure BaudRate Generator
    U2BRG = 10;     //BaudRate = 115200 ->(20000000 / (16 * 115200)) - 1 = 10
    U2MODEbits.BRGH = 0;
    // 2 – Configure number of data bits, parity and number of stop bits(see U2MODE register)
    U2MODEbits.PDSEL = 0;   //00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;   //0 = 1 Stop bit
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;

    // Configure UART2 interrupts, with RX interrupts enabled and TX interrupts disabled:
    //enable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0; 
    //set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 1;
    //clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    //define RX interrupt mode (URXISEL bits)
    U1STAbits.URXISEL=0;        //has 1 character
    // Enable global Interrupts
    
   
}

void _int_(4) isr_T1(void){
    // Start A/D conversion
    AD1CON1bits.ASAM = 1;
    // Reset T1IF flag
    IFS0bits.T1IF = 0;
}


void _int_(12) isr_T3(void){
    // Send "voltage" value to displays (global variable)
    send2displays(voltage);
    // Reset T3IF flag
    IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void)
{
    int *p = (int *)(&ADC1BUF0);
    int i;
    double average = 0;
    // Calculate buffer average (8 samples)
    for (i = 0; i < num; i++){
        average += p[i * 4];
    }
    putChar(average);
    average = average/ num;
    // Calculate voltage amplitude
    voltage = (average * 33 + 511)/1023;
    // Convert voltage amplitude to decimal. Copy it to "voltage"
    voltage = toBcd(voltage);
    putChar(voltage);
    
    // Update variables "voltMin" and "voltMax"
    if(voltage < voltMin)
        voltMin = voltage;
    if(voltage > voltMax)
        voltMax = voltage;

    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;
}

void _int_(32) isr_uart2(void){
    char c = U2RXREG; // Read character from FIFO
    if(c == 'M')
        // Send "voltMax" to the serial port UART2
    else if(c == 'm')
        // Send "voltMin" to the serial port UART2

    // Clear UART2 rx interrupt flag
    IFS1bits.U2RXIF = 0;
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

unsigned char toBcd(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
} 
