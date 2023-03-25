#include <detpic32.h>
int lado = 0;
static const char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
void delay(int ms) {
    for(;ms>0;ms--){
        resetCoreTimer();
        while(readCoreTimer()<20000);
    }
}

void send2disp(int valor, int base){
    int i;
    for(i=0;i<=1;i++){
        if(lado){
            int b = valor % base;
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
            LATB = (LATB & 0x80FF) | (display7Scodes[b]<<8);
            delay(1);
        }
        else {
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
            int a = valor/base;
            LATB = (LATB & 0x80FF) | (display7Scodes[a]<<8);
            delay(1);
        }
        lado = !lado;
    }
}


int main() {
    TRISB = (TRISB & 0XFFF0) | 0X000F; // dipswitch?
    TRISB = (TRISB & 0x80FF);// display -> output
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0; // rd5 e rd6 output displays
    TRISE = TRISE & 0xFF00; // leds 0-7 output

    LATDbits.LATD5 = 0;//reset
    LATDbits.LATD6 = 0;

    int count = 0;
    char ch;
    int i = 0;
    int temp = 0;
    int addcount =0;

    while(1){
    int ler_dipswitch = PORTB & 0x000F;//ler dipswitch
    if (count == 60) count=0; // dar reset a 60
    LATE = (LATE & 0xFF00) | count;

    if(addcount==20){
        count++;
        addcount=-1;
    }
    addcount++;


    switch(ler_dipswitch){


    case 0:{
        LATDbits.LATD5 = 0;//reset
        LATDbits.LATD6 = 0;
        delay(10);
        break;
    }


    case 2:{
        
        ch = inkey();

            switch(ch){
                case '1':{
                    temp=10;
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                    break;
                }
                case '2':{
                    temp=20;
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                    break;
                }
                case '3':{
                    temp=30;
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                    break;
                }

                case '4':{
                    for(i=0;i<5;i++){
                        temp=40;
                        send2disp(temp,10);
                    }
                    break;
                }

                case '5':{
                    temp=50;
                    for(i=0;i<5;i++){
                    send2disp(temp,10);
                    }
                    break;
                }

                case '6':{
                    temp=60;
                    for(i=0;i<5;i++){
                    send2disp(temp,10);
                    }
                    break;
                }

                case '7':{
                    temp=70;
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                    break;
                }

                case '8':{
                    temp=80;
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                    break;
                }

                case '9':{
                    temp=90;
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                    break;
                }

                default:{
                    for(i=0;i<5;i++){
                        send2disp(temp,10);
                    }
                break;
                }
            }
        break;
    }

    case 4:{
        ch = inkey();
        
        switch(ch){
            case '1':{
                temp=1;
                for(i=0;i<5;i++){

                    send2disp(temp,10);
                }
                break;
            }
            case '2':{
                temp=2;
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
                break;
            }
            case '3':{
                temp=3;
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
                break;
            }

            case '4':{
                temp=4;
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
                break;
            }

            case '5':{
                temp=5;
                for(i=0;i<5;i++){
                send2disp(temp,10);
                }
                break;
            }

            case '6':{
                temp=6;
                for(i=0;i<5;i++){
                send2disp(temp,10);
                }
                break;
            }

            case '7':{
                temp=7;
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
                break;
            }

            case '8':{
                temp=8;
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
                break;
            }

            case '9':{
                temp=9;
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
                break;
            }

            default:{
                for(i=0;i<5;i++){
                    send2disp(temp,10);
                }
            break;
            }
        }
        break;
    }

    case 6:{
        for(i=0;i<5;i++){
          send2disp(count, 16);
        }

        break;
    }
    
    default:{ 

        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 0;
        delay(10);
        break;}
    }

    }

}


