#include <stdio.h>

#define MAX 5

int main(void){
    int i;
    float array[5];

    printf("Input the 5 members of the array:\n");

    for(i = 0; i < 5; i++){
        scanf("%e", &array[i]);
    }

    for(i = 0; i < 5; i++){
        if(array[i] < MAX){
            printf("A[%d] = %.1f\n",i,array[i]);
        }
    }

    return 0;
}