#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void DisplayPol(double* coef, unsigned int degree) {

    printf("Pol(x) = ");

    int num = degree;

    for(int i = 0; i < num; i++){
        printf("%0.3f * x^%u + ", coef[i], degree--);
    }

    printf("%0.3f\n", coef[degree]);
}

int* read(unsigned int *degree){

    assert(degree != NULL);
    
    printf("Write down your coefficients knowing that p[0] is the coefficient of the largest degree term and p[n] is the coefficient of the zero-degree term. (n it's the degree of the polynom)");
    printf("What's the degree? ");
    scanf("%d", degree);
    
    int* polynom = malloc(*degree * sizeof(int));
    if(polynom == NULL){
        *degree = 0;
        return NULL;
    }

    for(size_t i = 0; i < *degree; i++){
        printf("p[%lu] = ", i);
        scanf("%d", &polynom[i]);
    }

    return polynom;
}

int main(void){

    // unsigned int degree = 4;
    // double p[5] = {1, 4, 1, 4, 0};
    // DisplayPol(p, degree);

    int degree;
    read(&degree);

}