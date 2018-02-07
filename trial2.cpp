#include <iostream>
#include "include/vector.h"

int main()
{
  vector A;

  A.x = 1;
  A.y = 1;
  A.z = 1;

  double l = A.getMagnitude();

  std::cout<<"Length is " << l << std::endl;


}
