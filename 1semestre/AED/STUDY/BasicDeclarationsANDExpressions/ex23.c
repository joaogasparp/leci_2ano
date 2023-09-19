#include <stdio.h>

int main(void){
    int a, b, c, perimeter;

    printf("Input the first number: "); 
    scanf("%d", &a);
    printf("Input the second number: "); 
    scanf("%d", &b);
    printf("Input the third number: "); 
    scanf("%d", &c);

    if(a+b>c && a+c>b && b+c>a){
        perimeter = a+b+c;
        printf("Perimeter = %d\n", perimeter);
    }else {
        printf("Incorrect values to form a triangle\n");
    }

    return 0;
}