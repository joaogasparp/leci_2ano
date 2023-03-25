#include <detpic32.h>

void delay(int time);
void seg(unsigned char num);

int main(void){

    TRISE = (TRISE & 0xFF80);
    TRISB = (TRISB & 0x80FF)| 0x0003;
    TRISD = (TRISD & 0xFF9F);

    int count = 0;

    int i = 0;
    char read = 0, num = 0;
    while (1){  
    
        LATE = (LATE & 0xFF80) | count;
        if(++count>60)
            count = 0;

            switch (PORTB & 0x0003){

                case 0x00:
                    LATD = LATD & 0xFF9F;
                    delay(200);
                    break;

                case 0x01:
                    i = 0;
                    read = inkey();
                    if(read <= '9' & read > '0'){
                        num = read;
                    }
                    do{
                        num = num & 0x0F;
                        seg(num );
                        delay(10);        //100hz
                    }while(++i < 20);     //5hz
                    break;

                case 0x02:
                    i = 0;
                    read = inkey();
                    if(read <= '9' & read > '0'){
                        num = (read << 4);
                    }
                    do{
                        num = num & 0xF0;
                        seg(num);
                        delay(10);        //100hz
                    }while(++i < 20);     //5hz
                    break;

                case 0x03:
                    i = 0;
                    do{
                        seg(count);
                        delay(10);        //100hz
                    }while(++i < 20);     //5hz
                    break;
                
        }
    }
}

void seg(unsigned char num){
    static const char seg7 [] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char flag = 0;

    unsigned char low = num & 0x0F;
    unsigned char high = num >> 4;

    if (flag == 1){
        LATD=(LATD & 0xFF9F)| 0x0040;
        high=seg7[high];
        LATB=(LATB & 0x80FF) | high << 8;
    }
    else{
        LATD=(LATD & 0xFF9F)| 0x0020; 
        low=seg7[low];
        LATB=(LATB & 0x80FF) | low << 8;
    }
    flag=!flag; 

}

void delay(int time){
    resetCoreTimer();
    while(readCoreTimer()<20000 * time);
}
