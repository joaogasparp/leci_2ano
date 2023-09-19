#include <stdio.h>
#include <math.h>

int main() {
    printf("====================================\n");
    printf("n     2 to power n    2 to power-n\n");
    printf("====================================\n");

    for(int n; n <= 10; n++){
        printf("%-5d %-15.0f %.10f\n", n, pow(2,n), pow(2,-n));
    }

    printf("====================================\n");

    return 0;
}