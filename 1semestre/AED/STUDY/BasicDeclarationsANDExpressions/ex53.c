#include <stdio.h>

int main(void){
    int p,r,t,sint;

    printf("Input principle, Rate of interest & time to find simple interest: \n");
    scanf("%d%d%d",&p,&r,&t);

    sint=(p*r*t)/100;

    printf("Simple interest = %d\n",sint);

    return 0;
}