#include <stdio.h>

int main(void){
    int num, minim, maxim, i = 0, sum;
    double average;

    printf("Input a positive integer: ");
    scanf("%d", &num);

    if(num <= 0) {
        printf("No positive number entered\n");
        return 0;
    }else {
        minim = num;
        maxim = num;
        sum = num;
        i++;
    }

    while(num > 0){
        printf("Input next positive integer: ");
        scanf("%d", &num);
        if(num <= 0) {
            break;
        }else {
            i++;
            if(minim > num){
                minim = num;
            }else if(maxim < num){
                maxim = num;
            }
            sum += num;
        }
    }

    average = sum/i;

    printf("Number of positive values entered is %d\n", i);
    printf("Maximum value entered is %d\n", maxim);
    printf("Minimum value entered is %d\n", minim);
    printf("Average value is %.4f\n", average);

    return 0;
}