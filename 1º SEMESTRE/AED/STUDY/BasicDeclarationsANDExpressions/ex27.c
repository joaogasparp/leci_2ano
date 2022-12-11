#include <stdio.h>

int main(void){
    int i, num[5], countNEG = 0, countPOS = 0;

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
        if (num[i] > 0)
        {
            countPOS++;
        }else if(num[i] < 0) {
            countNEG++;
        }
    }

    printf("Number of positive numbers: %d\n", countPOS);
    printf("Number of negative numbers: %d\n", countNEG);

    return 0;
}