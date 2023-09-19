#include <stdio.h>

int main(void){
    int x, y, temp;

    printf("Input value for x & y:\n");
    scanf("%d%d",&x,&y);

    printf("Before swapping the value of x & y: %d %d\n",x,y);

    temp = x; 
    x = y;
    y = temp;

    printf("After swapping the value of x & y: %d %d\n",x,y);

    return 0;
}