#include <stdio.h>

int main(void){
    int lines, x=0, j=1, characters;

    printf("Input number of lines: ");
    scanf("%d", &lines);
    printf("Number of characters in a line: ");
    scanf("%d", &characters);

    for(int i = 1; i <= lines; i++){
        while(x<characters){
            printf("%d ", j++);
            x++;
        }
        x=0;
        printf("\n");
    }

    return 0;
}