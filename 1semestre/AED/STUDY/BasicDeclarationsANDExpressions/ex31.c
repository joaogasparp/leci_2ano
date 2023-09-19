#include <stdio.h>

int main(void){
    int num;

    printf("Input a number: ");
    scanf("%d", &num);

    if(num == 0){                                    
        printf("Number is zero (0)\n");
    }else if (num%2==0){                                       
        if(num > 0){
            printf("Positive Even\n");
        }else if(num < 0){
            printf("Negative Even\n");
        }
    }else {
        if(num > 0){
            printf("Positive Odd\n");
        }else if(num < 0){
            printf("Negative Odd\n");
        }
    }

    return 0;
}