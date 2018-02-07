// EQUATIONS.H
// Contains definition of constitutive equation classes
// 1. LinearSpring

///..........................................................................///

#pragma once
#include "vector.h"
#include "fiber.h"

//1...........................................................................

class LinearSpring
{
 public :

  double k; // Spring stiffness

  vector getForce(fiber fib); // Function to calculate force

  matrix getStiffness(fiber fib); // Function to calculate stiffness
};
