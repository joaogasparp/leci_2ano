#include <stdio.h>

int main(void){
    int numdays = 1329;
    int years, weeks, days, restyd;

    years = numdays / 365;
    restyd = numdays % 365;
    weeks = restyd / 7;
    days = restyd % 7;
    
    printf("Years: %d\n",years);
    printf("Weeks: %d\n",weeks);
    printf("Days: %d\n",days);

    return 0;
}