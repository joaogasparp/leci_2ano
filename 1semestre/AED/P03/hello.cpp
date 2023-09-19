/*
// Tomás Oliveira e Silva, AED, October 2021
**
** my first C++ program (compare with hello.c)
*/

#include <iostream>

int main(void)
{
  int x = 0;
  char nome[30];

  std::cout << "Digita um número: ";

  std::cin >> x;

  for(int i = 1; i < x+1; i++)
  {
    std::cout << i << "\n";
  }

  return 0;
}