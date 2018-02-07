#include <iostream>
#include <cmath>
#include "include/fiber.h"

int main()
{
  fiber A[2];

  A[1].n2x = 2;
  A[1].n2y = 3;

  updateFibLength(&A[1]);

  double lenA = A[1].getLength();
  double S1 = A[1].getStretch();

  A[1].n1x = -2;
  A[1].n1y = -5;
  updateFibLength(&A[1]);

  double lenB = A[1].getLength();
  double S2 = A[1].getStretch();

  std::cout << "Length of fiber is " << lenA << " lambda : " << S1 << std::endl;
  std::cout << "Lambda of fiber now is " << lenB << " lambda : " << S2 << std::endl;


}
