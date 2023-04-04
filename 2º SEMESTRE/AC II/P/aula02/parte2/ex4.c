// 1Hz = 1000 milisegundos
// 5Hz = 200 milisegundos
// 10Hz = 100 milisegundos

#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    int cnt1 = 0, cnt5 = 0, cnt10 = 0;
    int freq1 = 1000, freq5 = 200, freq10 = 100;
    int stop = 0;
    while (1) {
        char c = inkey();
        cnt1++;
        printf("\r%05d   %05d   %05d", cnt1, cnt5, cnt10);
        delay(1000);
        cnt5++;
        printf("\r%05d   %05d   %05d", cnt1, cnt5, cnt10);
        delay(200);
        cnt10++;
        printf("\r%05d   %05d   %05d", cnt1, cnt5, cnt10);
        delay(100);
        if(c == 'A' || c == 'a')
        {
            freq1 = freq1/2;            // 1Hz = 1000 mas 2Hz = 500
            freq5 = freq5/2;
            freq10 = freq10/2;
        }else if(c == 'N' || c == 'n')
        {
            freq1 = 1000;
            freq5 = 200;
            freq10 = 100;
        }else if(c == 'S' || c == 's')
        {
            stop = 1;
        }else if(c == 'R' || c == 'r')
        {
            stop = 0;
        }
        if(stop == 0){
            cnt1++;
            printf("\r%05d   %05d   %05d", cnt1, cnt5, cnt10);
            delay(freq1);
            cnt5++;
            printf("\r%05d   %05d   %05d", cnt1, cnt5, cnt10);
            delay(freq5);
            cnt10++;
            printf("\r%05d   %05d   %05d", cnt1, cnt5, cnt10);
            delay(freq10);
        }
    }
    return 0;
}
