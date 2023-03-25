void delay(int ms);

int main(void){
    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    while(1){
        delay(100);      //10HZ

        putChar('\r');
        cnt10++;
        
        if(cnt10 % 2 == 0){
            cnt5++;
        }
            

        if(cnt10 % 10 == 0){
            cnt1++;
        }

        printInt(cnt10, 10 | 5 << 16);
        putChar(' ');
        printInt(cnt5, 10 | 5 << 16);
        putChar(' ');
        printInt(cnt1, 10 | 5 << 16);
        putChar(' ');

    }
    return 0;
}
void delay(int ms){
    resetCoreTimer();
    while (readCoreTimer() < 20000 * ms);
}