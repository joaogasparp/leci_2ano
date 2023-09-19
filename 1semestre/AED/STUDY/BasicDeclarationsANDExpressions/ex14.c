#include <stdio.h>

int main(void){
    float distance,fuel;

    printf("Input total distance in km: ");
	scanf("%f", &distance);
	printf("Input total fuel spent in liters: ");
	scanf("%f", &fuel);
    
    printf("Average consumption (km/lt) = %.2f\n",distance/fuel);

    return 0;
}