#include <stdio.h>

int main(void){
    int num, i, sum = 0;

    printf("Input any number: ");
    scanf("%d",&num);

    printf("1 ");
    for (i = 2; i <= num; i++){
        printf("+ 1/%d ",i);
    }

    for (i = 1; i <= num; i++){
        sum += i;
    }

    printf("\n");
    printf("Sum = 1/%d\n",sum+1/num);

    return 0;
}