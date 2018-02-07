// NODE.H
// Defines class node

///..........................................................................///

#pragma once

class node
{
 public:
  double x, y, z; // X, Y and Z coordinates of the node

  enum position {nX = -1, pX = 1, nY = -2, pY = 2, nZ = -3, pZ = 3, internal = 0 }; // To check if node is on the boundary or inside the box

  position node_pos;

  node(){x = 0; y = 0; z = 0; node_pos = internal;} // Constructor function
};

double getNodeDistance(node *, node *); // Function to find distance between two nodes
