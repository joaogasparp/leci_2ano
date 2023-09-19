#include <stdio.h>
#include <math.h>

int main() {
    float x, n, y=0;

    printf("Input the values of x and n: ");
    scanf("%e %e", &x, &n);

    printf("x=%.2f; n=%.0f;\n", x, n);

    if(n < 0){
        printf("n has to be non-negative integer!\n");
        return 0;
    }

    y = pow(x,n);

    printf("x to power n=%f\n", y);

    return 0;
}