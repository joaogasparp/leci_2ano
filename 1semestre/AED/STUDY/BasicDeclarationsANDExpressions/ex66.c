#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#define N 50

int main() {
    int i;
    char str;
    FILE * fptr;
    fptr = fopen("rand.dat", "w");
    if (fptr == NULL) {
        printf("Error in creating output.dat\n");
        return 0;
    }
    srand(time(NULL));
    fprintf(fptr, "%d\n", N);
    for(i = 1; i <= N; i++){
        fprintf(fptr, "%0.4lf\n", (rand() % 2001 - 1000) / 2.e3);
    }
    fclose(fptr);
    fptr = fopen ("rand.dat", "r");  
    str = fgetc(fptr);
    while (str != EOF){
        printf ("%c", str);
        str = fgetc(fptr);
    }
    fclose(fptr);
    return 0;
}