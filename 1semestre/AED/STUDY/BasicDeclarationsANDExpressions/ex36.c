#include <stdio.h>

int main(void){
    int pass;

    printf("Input the password: ");
    scanf("%d", &pass);

    while(pass != 1234){
        printf("Incorrect password\n");
        printf("Input the password: ");
        scanf("%d", &pass);
    }

    printf("Correct password\n");

    return 0;
}