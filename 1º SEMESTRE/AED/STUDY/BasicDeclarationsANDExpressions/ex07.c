#include <stdio.h>

int main(void){
    int a = 125, b = 12345;
    long ax = 1234567890;
    short s = 4043;
    float x = 2.13459;
    double dx = 1.1415927;
    char c = 'W';
    unsigned long ux = 2541567890; 

    printf("a + c = %d\n",a+c);
    printf("x + c = %f\n",x+c);
    printf("dx + x = %f\n",dx+x);
    printf("((int) dx) + ax =  %ld\n",((int)dx)+ax);
    printf("a + x = %f\n",a+x);
    printf("s + b =  %d\n",s+b);
    printf("ax + b = %ld\n",ax+b);
    printf("s + c =  %hd\n",s+c);
    printf("ax + c = %ld\n",ax+c);
    printf("ax + ux = %lu\n",ax+ux);

    return 0;
}