// NETWORK.H
// Defines class network

///..........................................................................///

#pragma once
#include <iostream> 
#include "fiber.h"
#include "node.h"
#include "vector.h"
#include "equations.h"

using namespace std;

class network
{

  public:

  fiber *fibers; // Pointer to the fiber class with details of network fibers

  node *nodes; // Pointer to the node class with details of the network nodes

  int N_fibs, N_nodes; // Number of fibers and nodes in the network

  double x_bound[2], y_bound[2], z_bound[2]; // Network boundaries : [low, high]

  double x_area, y_area, z_area; // Area of network box faces
                                 // x_area is the area perpendicular to X axis

  vector *forces; // Forces of each fiber in the network in vector form

  LinearSpring lin_spr;


  network(); // Constructor function

  void readNetwork(string filename); // Function to read in network

  void getFibForces(); // Function to calculate forces in each fiber

  double *getJacobian(); // Function to calculate Jacobian 
  
  void setBoundary(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax); // Sets the network boundaries to input values

  void getBoundNodes(); // Finds nodes on network boundary

  void updateNetwork(); // Update lengths of all fibers

  void updateFiberClass(); // Update nodal positions in class fiber to match nodes                              in network

  void stretchNetwork(vector stretch); // Stretches network by multiplying network                                       // nodes with stretch values given in                                             // stretch. Min faces remain fixed
};

