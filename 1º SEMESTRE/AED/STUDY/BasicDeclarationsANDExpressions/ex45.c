#include <stdio.h>

int main(void){
    float count;

    for (int i = 1; i <= 50; i++){
        count += (float)1/i;
    }

    printf("Value of S: %.2f",count);

    return 0;
}