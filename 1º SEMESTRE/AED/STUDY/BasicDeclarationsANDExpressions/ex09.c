#include <stdio.h>

int main(void){
    int x, y;

    printf("\nInput the first integer: "); 
    scanf("%d", &x);
    printf("\nInput the second integer: ");
    scanf("%d", &y);

    printf("\nSum of the above two integers = %d\n", x+y);

    return 0;
}