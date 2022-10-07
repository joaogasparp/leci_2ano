#include <stdio.h>

// CALL-BY-VALUE
void swap1(int a, int b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// CALL-BY-POINTERS
// BASICAMENTE SÓ ESTA FUNCÃO COM POINTERS
// É QUE FUNCIONA REALMENTE, A OUTRA ACABA POR
// SER "IGNORADA"
void swap2(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main(void){
    int x = 1;
    int y = 2;
    swap1(x, y);
    printf("x=%d | y=%d\n", x,y);
    printf("---------\n");
    swap2(&x, &y);
    printf("x=%d | y=%d\n", x,y);
    return 0;
}