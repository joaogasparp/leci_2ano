#include <stdio.h>

int main(void){
    int num;

    printf("Input a number: ");
    scanf("%d", &num);

    for (int i = 0; i < 101; i++)
    {
        if(i % num == 3)
        {
            printf("%d\n",i);
        } 
    }
    
    return 0;
}