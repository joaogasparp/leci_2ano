#include <stdio.h>

int main(void){
    int num1, num2, sum = 0;
    printf("Input a pair of numbers (for example 10,2):\nInput first number of the pair: ");
    scanf("%d", &num1);
    printf("Input second number of the pair: ");
    scanf("%d", &num2);

    if(num1>num2){
        int temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    printf("List of odd numbers: ");

    for(int i = num1; i < num2+1; i++){
        if(i%2 != 0){
            sum += i;
            printf("%d\n", i);
        }
    }

    printf("Sum = %d\n", sum);

    return 0;
}