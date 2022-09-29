#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[argc]){
    for (size_t i = 0; i < argc; i++)
    {
        char *token = argv[i];
        if (IsInteger(token)){
            printf("argv[%2u] = \"%s\" integer value: %ld\n", i, token, atol(token));
        } else {
            printf("argv[%2u] = \"%s\"\n", i , token);
        }
    }
    return 0;
}