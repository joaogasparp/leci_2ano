#include <stdio.h>

int main(void){
    int amount, total;

    printf("Input the amount: ");
    scanf("%d", &amount);

    total = amount / 100;
    printf("%d Note(s) of 100.00\n",total);

    amount = amount - (total*100);
    total = amount/50;
    printf("%d Note(s) of 50.00\n",total);

    amount = amount - (total*50);
    total = amount/20;
    printf("%d Note(s) of 20.00\n",total);

    amount = amount - (total*20);
    total = amount/10;
    printf("%d Note(s) of 10.00\n",total);

    amount = amount - (total*10);
    total = amount/5;
    printf("%d Note(s) of 5.00\n",total);

    amount = amount - (total*5);
    total = amount/2;
    printf("%d Note(s) of 2.00\n",total);

    amount = amount - (total*2);
    printf("%d Note(s) of 1.00\n",amount);

    return 0;
}