#include <stdio.h>

int main(void){
    int array[5], i, length, min, pos;

    printf("Input the length of the array:\n");
    scanf("%d", &length);

    printf("Input the %d members of the array:\n", length);

    for (i = 0; i < length; i++){
        scanf("%d", &array[i]);
    }

    min = array[0];
    pos = 0;

    for (i = 1; i < length; i++){
        if (min > array[i])
        {
            min = array[i];
            pos = i;
        }
    }

    printf("Smallest Value: %d\n", min);
    printf("Position of the element: %d\n",pos);

    return 0;
}