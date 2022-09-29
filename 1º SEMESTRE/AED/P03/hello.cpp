/*
// Tomás Oliveira e Silva, AED, October 2021
**
** my first C++ program (compare with hello.c)
*/

#include <iostream>

int main(void)
{
  std::cout << "Hello world!\n"; // "same" as printf("Hello world\n");
  for (int i = 1; i < 11; i++)
  {
    printf("%d\n", i);
  }
  return 0;
}
