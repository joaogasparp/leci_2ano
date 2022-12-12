#include <stdio.h>

int main(void){
    int sum = 0, marks, a=0;
    float average;

    printf("Input Mathematics marks (o to terminate): ");

    for (int i = 0; ; i++){
        scanf("%d", &marks);
        if(marks<=0){ 
            break; 
        }
        sum += marks;
        a++;
    }

    average = (float)sum/(float)a;
    printf("Average marks in Mathematics: %.2f\n", average);

    return 0;
}