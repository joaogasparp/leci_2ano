#include <stdio.h>

int main(void){
    int num1, num2;

    printf("Input the first number: "); 
    scanf("%d", &num1);
    printf("Input the second number: "); 
    scanf("%d", &num2);

    if(num1>num2){
        int temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    if(num2%num1==0){
        printf("Multiplied!\n");
    }else {
        printf("Not Multiplied!\n");
    }

    return 0;
}