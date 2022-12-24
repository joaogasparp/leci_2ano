#include <stdio.h>

int main() {
    char chr;

    printf("\n");

    for(chr = 65; chr <= 90; chr++) {
        printf("[%2d-%c] ", chr, chr);
    }

    printf("\n");
    printf("\n");

    for(chr = 97; chr <= 122; chr++) {
        printf("[%2d-%c] ", chr, chr);
    }

    printf("\n");
    printf("\n");

    return 0;
}