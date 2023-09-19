#include <stdio.h>

int main(void){
    int a, b;

    printf("Integer value = ");
    scanf("%d",&a);

    a<<=2;
    b=a;

    printf("The left shifted data is = %d\n",b);

    return 0;
}