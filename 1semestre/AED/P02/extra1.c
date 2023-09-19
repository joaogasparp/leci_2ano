#include <stdio.h>

int printArray(const char n1, const int *a){
    printf("%c: \n", n1);
    for(int i = 0;i < 12;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

int cumulativeSum(const char n2, const int *a, int *b){
    int c;
    for(int i = 0;i < 12;i++){
        c += a[i];
        b[i] = c;
    }
    printArray('b', b);
    return 0;
}

int main(void){
    int a[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int b[12];
    printArray('a', a);
    cumulativeSum('b', a, b);
    return 0;
}