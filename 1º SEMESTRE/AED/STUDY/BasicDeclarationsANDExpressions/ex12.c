#include <stdio.h>

int main(void){
    char id[10];
    int hour;
    double value;

    printf("Input the Employees ID(Max. 10 chars): ");
	scanf("%s", &id);
	printf("Input the working hrs: ");
	scanf("%d", &hour);
	printf("Salary amount/hr: ");
	scanf("%lf", &value);

    printf("Employess ID = %s\n",id);
    printf("Salary = U$ %.2lf\n", hour*value);    

    return 0;
}