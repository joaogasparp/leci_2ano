#include <stdio.h>

int main(void){
    int array[5], min, j;

    printf("Input the 5 members of the array:\n");

    for (int i = 0; i <= 4; i++)
    {
        scanf("%d", &array[i]);
        if(array[i] < array[i-1]){
            j = i;
            min = array[i];
        }
    }

    printf("A[%d] = %.1f",j,(float)min);

    return 0;
}