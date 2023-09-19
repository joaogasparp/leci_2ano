#include <stdio.h>

int main(void){
    int lines, x=0, j=1;

    printf("Input number of lines: ");
    scanf("%d", &lines);

    for(int i = 1; i <= lines; i++){
        printf("%d %d %d\n",j,j*j,j*j*j);
        j++;
    }

    return 0;
}