#include <stdio.h>
#include <math.h>

int main(void){
    float x, result;

    printf("Input value of x: ");
    scanf("%e", &x);

    result = sin(1/x);

    printf("Value of sin(1/x) is %.4f\n", result);

    return 0;
}