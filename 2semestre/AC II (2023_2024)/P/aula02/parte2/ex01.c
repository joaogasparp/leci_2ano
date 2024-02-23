// 1Hz = 1000 milisegundos
// 5Hz = 200 milisegundos
// 10Hz = 100 milisegundos

#include <detpic32.h>

void delay(unsigned int ms);

int main(void){
    int cnt1 = 0, cnt5 = 0, cnt10 = 0;

    while(1){
        delay(100);

        putChar('\r');
        cnt10++;
        
        if(cnt10 % 2 == 0){
            cnt5++;
        }

        if(cnt10 % 10 == 0){
            cnt1++;
        }

        printf("\r%05d\t%05d\t%05d", cnt1, cnt5, cnt10);
    }
    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
