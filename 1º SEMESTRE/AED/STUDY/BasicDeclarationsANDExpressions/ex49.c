#include <stdio.h>

int main(void){
    int n[5], i, x;
	printf("Input the first number of the array:\n");

	scanf("%d", &x);
	for(i = 0; i < 5; i++){
		n[i] = x;
		x = 3*x;
	}

	for(i = 0; i < 5; i++){
		printf("n[%d] = %d\n", i, n[i]);
	}

    return 0;
}