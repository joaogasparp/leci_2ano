#include <stdio.h>

int main(void){
    int num;

    printf("Input a number: ");
    scanf("%d", &num);

    for(int i = 1; i < num+1; i++)
    {
        if(i % 2 == 0){                                       
            printf("%d^2 = %d\n", i,i*i);
        }
    }

    return 0;
}