#include <stdio.h>
#include <math.h>

int main(void){
    int num, sum = 0, j = 1;

    printf("Input a positive number less than 100: ");
    scanf("%d", &num);

    if(num >= 100 || num <= 0) {
        printf("The given number is out of rage\n");
        return 0;
    }

    for (int i = 1; j <= num; i++) {
        sum += pow(j,4);
        j += i;
    }
    
    printf("Sum of the series is %d\n", sum);
    
    return 0;
}