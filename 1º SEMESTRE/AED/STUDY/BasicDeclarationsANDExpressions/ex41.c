#include <stdio.h>

int main(void){
    int lines, x=0, j=1;

    printf("Input number of lines: ");
    scanf("%d", &lines);

    for(int i = 1; i <= lines; i++){
        while(x<3){
            printf("%d ", j++);
            x++;
        }
        x=0;
        printf("\n");
    }

    return 0;
}