#include <detpic32.h>

void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

int counter;

int main(void)
{
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    // Timer 1 (10Hz)
    T1CONbits.TCKPS = 5;    // 1:32 -> 101
    PR1 = 62499;            // (625000/10)-1 = 62499
    TMR1 = 0;
    T1CONbits.TON = 1;
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    //Timer 2 (50Hz)
    T2CONbits.TCKPS = 3;    // 1:8 -> 011
    PR2 = 249999;           // (2500000/10)-1 = 249999
    TMR2 = 0;
    T2CONbits.TON = 1;
    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    EnableInterrupts();
    while(1)
    {
        char c = inkey();
        if (c == 0) {
            continue;
        }
        switch (c) {
            case '0':
                PR1 = 29999;
                break;
            case '1':
                PR1 = 14999;
                break;
            case '2':
                PR1 = 7499;
                break;
            case '3':
                PR1 = 3749;
                break;
            case '4':
                PR1 = 1874;
                break;
        }
        printStr("\nNova frequência: ");
        putChar(c);
    }
    return 0;
}

void _int_(8) isr_T2(void)
{
    send2displays(toBcd(counter));
    IFS0bits.T2IF = 0;
}

void _int_(4) isr_T1(void)
{
    counter++;
    if (counter == 99)
    {
        counter = 0;
    }
    printInt(counter, 16 | 2 << 16);
    IFS0bits.T1IF = 0;
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

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}
