#include <stdio.h>

int main(void){
    float dist, inch;

    printf("Input the distance in cm: ");
    scanf("%f", &dist);

    inch = dist*0.393700787;

    printf("Distance of %.2f cm is = %.2f inches\n", dist, inch);

    return 0;
}