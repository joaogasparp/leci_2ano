#include <stdio.h>

int main() {
    int i, j, count = 0, line = 0;

    printf("The prime number between 1 and 199 are: \n");

    for(i = 2; i < 200; i++) {
        count = 0;
        for (j = 1; j <= i; j++) {
            if(i % j == 0) {
                count++;
            }
        }
        if(count == 2) {
            printf("%d ", i);
            line++;
            if(line == 20) {
                printf("\n");
            }
        }
    }

    printf("\n");

    return 0;
}