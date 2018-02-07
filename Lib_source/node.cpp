// This file contains the definition of :
// 1. getNodeDistance(node *, node *)

///..........................................................................///

#include <cmath>
#include "../include/node.h"

double getNodeDistance(node *a, node *b)
{
  // Gets the Euclidian distance between two points of class : node

  double del_x = a->x - b->x;
  double del_y = a->y - b->y;
  double del_z = a->z - b->z;

  // Calculate the Euclidian distance between given nodes

  return(sqrt(del_x*del_x + del_y*del_y + del_z*del_z));
}
