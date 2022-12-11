#include <stdio.h>

int main(void){
    for (int i = 1; i < 51; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d ",i);
        }
    }

    printf("\n");
    
    return 0;
}