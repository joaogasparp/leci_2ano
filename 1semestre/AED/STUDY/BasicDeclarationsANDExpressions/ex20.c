#include <stdio.h>
#include <math.h>   

int main() {
	double a, b, c, pr1;  	

	printf("Input the first number(a): "); 
    scanf("%lf", &a);
    printf("Input the second number(b): "); 
    scanf("%lf", &b);
    printf("Input the third number(c): "); 
    scanf("%lf", &c);

    pr1 = (b*b) - (4*(a)*(c));

    if(pr1 > 0 && a != 0){
		double x, y;
		pr1 = sqrt(pr1);
		x = (-b + pr1)/(2*a);
		y = (-b - pr1)/(2*a);
		printf("Root1 = %.5lf\n", x);
		printf("Root2 = %.5lf\n", y);
	}else {
		printf("Impossible to find the roots.\n");
	}

    return 0;
}