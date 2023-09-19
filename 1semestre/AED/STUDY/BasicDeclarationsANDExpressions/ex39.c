#include <stdio.h>

int main(void){
    int num1, num2, total = 0;

    printf("Input the first integer: ");
    scanf("%d", &num1);
    printf("Input the second integer: ");
    scanf("%d", &num2);

    if(num1>num2){
        int temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    for(int i = num1; i < num2+1; i++){
        if((i % 17) != 0){
            total += i;
        }
    }

    printf("Sum = %d\n", total);

    return 0;
}