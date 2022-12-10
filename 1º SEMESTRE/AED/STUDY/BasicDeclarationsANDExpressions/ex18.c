#include <stdio.h>

int main(void){
    int numdays, years, month, days, restyd;

    printf("Input no. of days: ");
    scanf("%d", &numdays);

    years = numdays / 365;
    numdays = numdays - years*365;
    month = numdays / 30;
    days = numdays - month*30;

    printf("%d Year(s)\n%d Month(s)\n%d Day(s)\n",years,month,days);
    
    return 0;
}