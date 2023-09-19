#include <stdio.h>

int main(void){
    int num, x, rnum = 0;

    printf("The original number = ");
    scanf("%d",&num);

    while(num != 0){
        x = num % 10;
        rnum = rnum * 10 + x;
        num /= 10;
    }

    printf("The reverse of the said number = %d\n", rnum);

    return 0;
}