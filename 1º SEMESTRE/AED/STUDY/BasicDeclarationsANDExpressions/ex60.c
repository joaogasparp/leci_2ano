#include <stdio.h>

int main(void){
    enum week{Sun, Mon, Tue, Wed, Thu, Fri, Sat};
    printf("Sun = %d", Sun);
    printf("\nMon = %d", Mon);
    printf("\nTue = %d", Tue);
    printf("\nWed = %d", Wed);
    printf("\nThu = %d", Thu);
    printf("\nFri = %d", Fri);
    printf("\nSat = %d\n", Sat);

    return 0;
}