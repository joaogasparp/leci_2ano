//
// Tomás Oliveira e Silva, AED, October 2021
//
// list all command line arguments
//

#include <stdio.h>

int main(int argc,char *argv[argc])
{
  for(int i = 0;i < argc;i++)
    printf("argv[%2d] = \"%s\"\n",i,argv[i]);
  return 0;
}
