#include <stdio.h>

int main(void){
    int i, num[5],total = 0;

    printf("Input the first number: "); 
    scanf("%d", &num[0]);
    printf("Input the second number: "); 
    scanf("%d", &num[1]);
    printf("Input the third number: "); 
    scanf("%d", &num[2]);
	printf("Input the fourth number: "); 
    scanf("%d", &num[3]);
    printf("Input the fifth number: "); 
    scanf("%d", &num[4]);

    for (i = 0; i < 5; i++)
    {
        if(num[i] % 2 != 0){
            total += num[i];
        }
    }

    printf("Sum of all odd values: %d\n",total);

    return 0;
}