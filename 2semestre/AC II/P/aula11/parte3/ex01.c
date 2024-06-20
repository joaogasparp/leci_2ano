#include <detpic32.h>

volatile int voltage = 0;       // Global variable
double average = 0;
volatile int voltMin = 1023;
volatile int voltMax = 0;

void configureAll();
unsigned char toBcd(unsigned char value);
void send2displays(unsigned char value);
void putc(char byte);

int main(void)
{
    configureAll();
    EnableInterrupts();         // Global Interrupt Enable
    while(1);
    return 0;
}


void configureAll()
{
    // digital I/O
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    // analog input e A/D module
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // timers T1 and T3
    T1CONbits.TCKPS = 2;
    PR1 = 62499;
    TMR1 = 0;
    T1CONbits.TON = 1;

    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T1CONbits.TON = 1;

    // interrupts
    IPC6bits.AD1IP = 3;     // configure priority of A/D interrupts
    IEC1bits.AD1IE = 1;     // Enable A/D interrupts
    IFS1bits.AD1IF = 0;     // Reset timer AD interrupt flag

    IPC1bits.T1IP = 1;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    // Configure UART2: 115200, N, 8, 1
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;
    // Configure UART2 interrupts, with RX interrupts enabled and TX interrupts disabled:
    // enable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    // set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 1;
    // clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    // define RX interrupt mode (URXISEL bits)
    U2STAbits.URXISEL = 0;
}

void _int_(4) isr_T1(void)
{
    AD1CON1bits.ASAM = 1;       // Start A/D conversion
    IFS0bits.T1IF = 0;          //  Reset timer T1 interrupt flag
}

void _int_(12) isr_T3(void)
{
    send2displays(voltage);     // Send "voltage" value to displays (global variable)
    IFS0bits.T3IF = 0;          //  Reset timer T3 interrupt flag
}

void _int_(27) isr_adc(void)
{
    int i;
    int *p = (int *)(&ADC1BUF0);
    for(i = 0; i < 8; i++)
    {
        average += p[i*4];
    }
    average = average / 8;
    voltage = (average * 33 + 511) / 1023;
    voltage = toBcd(voltage);
    putChar(voltage);

    // Update variables "voltMin" and "voltMax"
    if(voltage < voltMin) {
        voltMin = voltage;
    }
    if(voltage > voltMax) {
        voltMax = voltage;
    }

    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;         
}

unsigned char toBcd(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
    static char displayFlag = 0;
    int digit_low = value % 10;
    int digit_high = value / 10;
    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_low] << 8));
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_high] << 8));
    }
    displayFlag = !displayFlag;
}

void _int_(32) isr_uart2(void)
{
    char c = U2RXREG;
    if(c == 'M'){
        putc('M');
        putc('a');
        putc('x');
        putc(':');
        putc(voltMax);
        putc('V');
        // Send "voltMax" to the serial port UART2
    } else if(c == 'm') {
        putc('m');
        putc('i');
        putc('n');
        putc(':');
        putc(voltMin);
        putc('V');
        // Send "voltMin" to the serial port UART2
    }
    // Clear UART2 rx interrupt flag
    IFS1bits.U2RXIF = 0;
}

void putc(char byte)
{
    // wait while UART2 UTXBF == 1
    while(U2STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}
