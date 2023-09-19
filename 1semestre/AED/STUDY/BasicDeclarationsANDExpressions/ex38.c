#include <stdio.h>

int main(void){
    int x, y;
	float div_result;

    printf("Input two numbers:\n");
	printf("x: ");
    scanf("%d", &x);
    printf("y: ");
    scanf("%d", &y);

    if(y != 0) {
	    div_result = x/y;
		printf("%.1f\n", div_result);
	}else {
	    printf("Division not possible\n");
	}

    return 0;
}