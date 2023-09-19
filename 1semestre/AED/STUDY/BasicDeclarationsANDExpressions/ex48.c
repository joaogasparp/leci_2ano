#include <stdio.h>

int main(void){
    int array[7];

    printf("Input the 7 members of the array:\n");

    for (int i = 0; i <= 7; i++)
    {
        scanf("%d", &array[i]);
        if(array[i]<=0){
            array[i] = 100;
        }
    }

    printf("Array values are:\n");

    for (int j = 0; j <= 7; j++)
    {
        printf("n[%d] = %d\n",j,array[j]);
    }

    return 0;
}