#include <detpic22.h>

unsigned char digitos;

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
    static char displayFlag = 0; // static variable: doesn't loose its value between calls to function
    int digit_low = value % 10;
    int digit_high = value / 10;
    // if "displayFlag" is 0 then send digit_low to display_low
    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_low] << 8));
    }
    // else send digit_high to didplay_high
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = ((LATB & 0x80FF) | (display7Scodes[digit_high] << 8));
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}

void _int_(8) isr_T2(void) {  // 0,01 sec
    send2displays(digitos);
    IFS0bits.T2IF = 0;  // reset flag
}

int main(void)
{
    // ports
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    TRISE = TRISE & 0xFFF0;
    LATE = LATE & 0xFFF0;
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;

    // Configure Timer T2 with interrupts enabled
    // K_prescaler = 3 ou seja 4
    T2CONbits.TCKPS = 2;    // 1:4 -> 010
    PR2 = 49999;            // (5000000/10)-1 = 49999
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 1; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag

    EnableInterrupts();
    while (1)
    {
        char c = getChar();
        if(c == '0')
        {
            LATE = LATE & 0x0001;
        }else if(c == '1')
        {
            LATE = LATE & 0x0002;
        }else if(c == '2')
        {
            LATE = LATE & 0x0004;
        }else if(c == '3')
        {
            LATE = LATE & 0x0008;
        }else
        {
            LATE = LATE & 0x000F;
            delay(10);
            LATE = LATE & 0xFFF0;
        }
    }

    return 0;
}