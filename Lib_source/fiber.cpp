// This file contains the definition of : 
// 1. fiber constructor
// 2. updateFibLength(fiber *)

///.........................................................................///

#include <cmath>
#include "../include/fiber.h"


fiber::fiber() // Constructor function
    {
      node1 = 0;
      node2 = 0;
      fib_length = 0;
      init_length = fib_length;
      fib_lambda = 1.0;
      n1x = n1y = n1z = 0;
      n2x = n2y = n2z = 0;
      fib_stat = alive;
      fib_type = 1;
      fib_radius = 0;

    }


void updateFibLength(fiber *a)
{
  // Updates the length of fiber pointed to by the fiber pointer a

  double del_x = a->n1x - a->n2x;
  double del_y = a->n1y - a->n2y;
  double del_z = a->n1z - a->n2z;

  // Calculate Euclidian distance between end nodes
  a->fib_length = sqrt(del_x*del_x + del_y*del_y + del_z*del_z);

  if(a->fib_length == 0){return;}// Check to see if fiber length is zero

  if(a->init_length == 0){a->init_length = a->fib_length;}// Check if first time

  a->fib_lambda = a->fib_length / a->init_length;

  return;

}


