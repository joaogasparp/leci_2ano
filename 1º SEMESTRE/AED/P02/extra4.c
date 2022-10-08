#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int* display(int *a, size_t size){

    if(size < 0){
        return NULL;
    }

    printf("Array: [ ");
    for(int i = 0; i < size-1; i++){
        printf("%d, ", a[i]);
    }

    printf("%d ]\n", a[size-1]);
    return 0;
}

int* read(size_t *size, int num){
    // pedir o n de elementos
    // alocar membros para o array e verificar se a alocação foi válida!!  usar: int* novo = malloc(n * sizeof(int)); if(novo == NULL ){*size = 0; return NULL;}
    // preenche o array elemento a elemento
    // "devolve" o tamanho do array
    // devolver o ponteiro para o início do array

    assert(size != NULL);

    int* array = malloc(*size * sizeof(int));
    if(array == NULL){
        *size = 0;
        return NULL;
    }

    for(size_t i = 0; i < *size; i++){
        printf("A_%d[%lu] = ", num, i);
        scanf("%d", &array[i]);
    }

    return array;
}

int* append(int *a1, size_t size1, int *a2, size_t size2){
    int c[size1 + size2];

    if(size1 < 0 || size2 < 0){
        return NULL;
    }

    size_t size3 = size1 + size2;
    for(int i = 0; i < size1; i++)
       c[i] = a1[i];
    for(int i = 0; i < size2; i++)     
        c[i + size1] =a2[i];

    if(c == NULL){
        size1 = 0;
        size2 = 0;
        return NULL;
    }

    printf("Merged ");

    display(c, size3);

    return 0;
}

int main(void){
    // size_t size1 = 3;
    // int a1[3] = {1, 2, 3};
    // display(a1, size1);

    // size_t size2 = 4;
    // int a2[4] = {4, 5, 6, 7};
    // display(a2, size2);

    size_t size3;
    printf("Array_1 size (> 0): ");
    scanf("%lu", &size3);
    assert(size3 > 0);
    size_t size4;
    printf("Array_2 size (> 0): ");
    scanf("%lu", &size4);
    assert(size4 > 0);

    append(read(&size3, 1), size3, read(&size4, 2), size4);    
    
    return 0;
}