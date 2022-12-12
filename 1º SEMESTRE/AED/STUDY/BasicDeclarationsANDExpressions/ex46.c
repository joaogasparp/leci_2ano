#include <stdio.h>

int main(void){
    double j=1, count=0, i, d;

    for(i = 1; i<=7 ; ){
        d = (i/j);
        count += d;
        j = j*2;
        i += 2;
    }

    printf("Value of series: %.2lf\n", count);

    return 0;
}