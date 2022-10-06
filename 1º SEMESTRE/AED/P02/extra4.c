#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void display(int *a, size_t size){
    printf("Array: [ ");
    for(int i = 0; i < size-1; i++){
        printf("%d, ", a[i]);
    }

    printf("%d ]\n", a[size-1]);
}

int* read(size_t *size){
    // pedir o n de elementos
    // alocar membros para o array e verificar se a alocação foi válida!!  usar: int* novo = malloc(n * sizeof(int)); if(novo == NULL ){*size = 0; return NULL;}
    // preenche o array elemento a elemento
    // "devolve" o tamanho do array
    // devolver o ponteiro para o início do array

    assert(size != NULL);

    size_t n;
    printf("Array size (> 0): ");
    scanf("%lu", &n);
    assert(n > 0);

    int* array = malloc(n * sizeof(int));
    if(array == NULL){
        *size = 0;
        return NULL;
    }

    for(size_t i = 0; i < n; i++){
        printf("A[%lu] = ", i);
        scanf("%d", &array[i]);
    }

    *size = n;

    display(array, n);
    return array;
}

int* append(int *a1, size_t size1, int *a2, size_t size2){
    int c[size1 + size2];

    size_t size3 = size1 + size2;
    for(int i = 0; i < size1; i++)
       c[i] = a1[i];
    for(int i = 0; i < size2; i++)     
        c[i + size1] =a2[i];

    display(c, size3);

    return c;
}

int main(void){
    // size_t size1 = 3;
    // int a1[3] = {1, 2, 3};
    // display(a1, size1);

    // size_t size2 = 4;
    // int a2[4] = {4, 5, 6, 7};
    // display(a2, size2);

    size_t size;
    read(&size);
    

    append(a1, size1, a2, size2);

    return 0;
}