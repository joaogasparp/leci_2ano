#include <stdio.h>

int main(void){
    int array[5], i, temp;

    printf("Input the 5 members of the array:\n");

    for (i = 0; i < 5; i++)
    {
        scanf("%d", &array[i]);
    }

    for (i = 0; i < 5; i++){
        if(i < (5/2)){
            temp = array[i];
            array[i] = array[5-(i+1)];
            array[5-(i+1)] = temp;
        }
    }

    for (i = 0; i < 5; i++)
    {
        printf("array_n[%d] = %d\n",i, array[i]);
    }

    return 0;
}