#include <stdio.h>

int main(void){
    int num, y, x = 0;

    printf("Input a positive number less than 500: ");
    scanf("%d", &num);

    y = num;

    if(num >= 500 || num <= 0) {
        printf("The given number is out of rage\n");
    }else {
        x += y % 10;
        y /= 10;
        x += y % 10;
        y /= 10;
        x += y % 10;
        printf("Sum of the digits of %d is %d\n", num, x);
    }

    return 0;
}