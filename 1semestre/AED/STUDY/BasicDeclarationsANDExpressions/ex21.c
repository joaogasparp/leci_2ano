#include <stdio.h>

int main(void){
    int num;

    printf("Input an integer: ");
    scanf("%d", &num);

    if(num <= 20 && num >= 0){
        printf("Range [0, 20].\n");
    }else if(num >= 21 && num <= 50){
        printf("Range [21, 50].\n");
    }else if(num >= 51 && num <= 80){
        printf("Range [51, 80].\n");
    }else {
	    printf("Outside the range.\n");
	}	

    return 0;
}