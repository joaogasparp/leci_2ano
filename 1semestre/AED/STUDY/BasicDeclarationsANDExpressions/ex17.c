#include <stdio.h>

int main(void){
    int numsec,hours,minutes,seconds,resthm;

    printf("Input seconds: ");
    scanf("%d", &numsec);

    hours = numsec / 3600;
    resthm = numsec % 3600;
    minutes = resthm / 60;
    seconds = resthm % 60;

    printf("H:M:S -> %d:%d:%d\n",hours,minutes,seconds);

    return 0;
}