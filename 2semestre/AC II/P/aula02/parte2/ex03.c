#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    int cnt1 = 0, cnt5 = 0, cnt10 = 0;
    int del = 100;

    while (1) {
        char c = inkey();
        delay(del);
        cnt10++;
        if(cnt10 % 2 == 0){
            cnt5++;
        }
        if(cnt10 % 10 == 0){
            cnt1++;
        }
        printf("\r%05d\t%05d\t%05d", cnt1, cnt5, cnt10);

        if (c == 'A') {
            del = del / 2;
        } else if (c == 'N') {
            del = 100;
        }
    }
    return 0;
}

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
