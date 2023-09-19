 #include <stdio.h>

 int main(void){
    int i, num[5],total = 0, max, numpos;


    printf("Input 5 integers:\n"); 
    scanf("%d", &num[0]);
    scanf("%d", &num[1]);
    scanf("%d", &num[2]);
    scanf("%d", &num[3]);
    scanf("%d", &num[4]);

    max = num[0];

    for (i = 0; i < 5; i++)
    {
        if(num[i] > max){
            max = num[i];
            numpos = i;
        }
    }
    
    printf("Highest value: %d\n", max);
    printf("Position: %d\n",numpos+1);

    return 0;
}