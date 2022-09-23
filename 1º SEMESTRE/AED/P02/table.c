//
// Tomás Oliveira e Silva, AED, October 2021
//
// program to print a table of the squares and square roots of some integers
//
// on GNU/Linux, run the command
//   man 3 printf
// to see the manual page of the printf function
//

#include <math.h>
#include <stdio.h>

void do_it(int N)
{
  int i;

  FILE *fptr;
  fptr = fopen("tabela.txt","w");
  
  fprintf(fptr, "n  sin(n)            cos(n)\n");
  fprintf(fptr, "-- ----------------- -----------------\n");

  for(i = 1;i <= N;i++)
    fprintf(fptr,"%2d %3.15f %17.15f\n", i, sin((double)i*(M_PI/180)), cos((double)i*(M_PI/180)));
  
  fclose(fptr);
}

int main(void)
{
  do_it(90);
  return 0;
}
