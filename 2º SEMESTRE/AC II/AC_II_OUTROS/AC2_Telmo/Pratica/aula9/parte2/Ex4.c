#include <detpic32.h>

void setPWM(unsigned int dutyCycle);

int main(void)
{
    //T3 a 100
    T3CONbits.TCKPS = 2;        
    PR3 = 49999;                         
    TMR3 = 0;                   
    T3CONbits.TON = 1;

    OC1CONbits.OCM = 6;     //PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =1;   //Use timer T3 as the time base for PWM generation
    OC1RS = 12500;          //Ton constant
    OC1CONbits.ON = 1;      //Enable OC1 module

    //Nao e necessario configurar a porta RD0 pois dando enable ao output OCx automaticamente
    //configura a sua porta como saida

    IPC3bits.T3IP = 3;          // Interrupt priority 2
    IEC0bits.T3IE = 1;          // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;          // Reset timer T3 interrupt flag

    //setPWM(0);  //aqui esta desligado
    //setPWM(50); //tem luz na metadae da intesidade
    setPWM(100);  //Maxima luz
    

    //reset 
    LATC = LATC & 0xBFFF;

    //Ports
    TRISC = TRISC & 0xBFFF;

    EnableInterrupts();

    while(1){
        // Read the value of port RD0 and write it on port RC14
        LATC = (PORTD & 0x0001) << 14;
    }

    return 0;
}

void _int_(12) isr_T3(void){
    IFS0bits.T3IF = 0;
}

void setPWM(unsigned int dutyCycle){
    // duty_cycle must be in the range [0, 100]
    if(dutyCycle >= 0 && dutyCycle <= 100){
        // Determine OC1RS as a function of "dutyCycle"
        OC1RS = ((PR3 + 1) * dutyCycle) /100;
    }
}
