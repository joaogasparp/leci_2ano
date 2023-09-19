#include <stdio.h>

int main(void){
    float array[4], dif, min, max;
    int i;

    printf("Input four numbers:\n");
    for(i = 0; i < 4; i++){
        scanf("%e", &array[i]);
    }

    min = array[0];
    max = array[0];
    for (i = 1; i < 4; i++){
        if(min > array[i]){
            min = array[i];
        }else if(max < array[i]){
                max = array[i];
        }  
    }
    
    dif = (float)max - (float)min;
    printf("Difference is %.4f\n", dif);

    return 0;
}