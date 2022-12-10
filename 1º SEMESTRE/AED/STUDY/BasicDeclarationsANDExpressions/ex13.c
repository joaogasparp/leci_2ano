#include <stdio.h>

int main(void){
    int n1,n2,n3;

    printf("Input a number: ");
	scanf("%d", &n1);
	printf("Input a number: ");
	scanf("%d", &n2);
    printf("Input a number: ");
	scanf("%d", &n3);

    if (n1 > n2 && n2 > n3){
        printf("Maximum value of the three integers = %d\n", n1);
    }else if(n1 < n2 && n2 > n3){
        printf("Maximum value of the three integers = %d\n", n2);
    }else{
        printf("Maximum value of the three integers = %d\n", n3);
    }

    return 0;
}