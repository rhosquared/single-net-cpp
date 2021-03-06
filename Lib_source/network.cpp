// This file contains the definitions of :
// 1. Constructor function for network
// 2. readNetwork(string filename)
// 3. updateNetwork()
// 4. getFibForces()
// 5. getBoundNodes()
// 6. setBoundary()
// 7. updateFiberClass()
// 8. stretchNetwork(vector stretch)
// 9. getJacobian()

///..........................................................................///

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "../include/vector.h"
#include "../include/fiber.h"
#include "../include/network.h"
#include "../include/equations.h"

//1................................................................................

network :: network()
{
  // Constructor function for class network

  N_fibs = N_nodes = 0;

  // Initialize boundaries to [-0.5, 0.5]
  x_bound[0] = y_bound[0] = z_bound[0] = -0.5;
  x_bound[1] = y_bound[1] = z_bound[1] = 0.5;

  // Face areas based on above boundaries
  x_area = z_bound[1] * y_bound[1];
  y_area = x_bound[1] * z_bound[1];
  z_area = x_bound[1] * y_bound[1];


}

//2................................................................................

void network :: readNetwork(string filename)
{

  // Read network details from .del type file
  // Network details read in include : 
  // Node coordinates
  // Fiber end nodes

  ifstream inFile; // File to be read
  int i, j; // Loop variables
  int fib_count = 0; // Fiber number 
  int DOF, n1, n2; // Intermittent storage variables


  inFile.open( filename.c_str() ); // Open network file

  inFile >> N_nodes >> DOF >> N_fibs; // First line has number of nodes and fibers

  fibers = (fiber *)calloc(N_fibs, sizeof(fiber)); // Memory allocation

  nodes = (node *)calloc(N_nodes, sizeof(node));

  forces = (vector *)calloc(N_nodes, sizeof(vector));

  // Temporary section....................
  lin_spr.k = 1000;

  while (!inFile.eof()) // Continue reading till End Of File
    {
      // Fiber number
      inFile >> fib_count;
      fib_count -= 1;

      // Read in end nodes of fiber
      inFile >> fibers[fib_count].node1 >> fibers[fib_count].node2;
      n1 = fibers[fib_count].node1;
      n2 = fibers[fib_count].node2;

      // Read in node coordinates

      inFile >> nodes[n1 - 1].x >> nodes[n1 - 1].y >> nodes[n1 - 1].z;
      inFile >> nodes[n2 - 1].x >> nodes[n2 - 1].y >> nodes[n2 - 1].z;

      // Set node coordinates in fiber class
      fibers[fib_count].n1x = nodes[n1 - 1].x;
      fibers[fib_count].n1y = nodes[n1 - 1].y;
      fibers[fib_count].n1z = nodes[n1 - 1].z;

      fibers[fib_count].n2x = nodes[n2 - 1].x;
      fibers[fib_count].n2y = nodes[n2 - 1].y;
      fibers[fib_count].n2z = nodes[n2 - 1].z;

      // inFile >> fibers[fib_count].fib_type;
      // Fiber type assignment 

    }
}

//3.................................................................................

void network :: updateNetwork()
{
  int i; // Loop variable

  for (i=0; i<N_fibs; i++)
    {
      updateFibLength(&fibers[i]); // Calculates fiber length and stretch
                                   // Defined in fiber.cpp and fiber.h
    }
}

//4................................................................................

void network :: getFibForces()
{
  updateNetwork(); // Update fiber lengths and stretch values

  int i; // Loop variable
  int const_eq = 0;
  vector F; // Fiber force
  int n1, n2; // Fiber end nodes

  for (i=0; i<N_fibs; i++)
    {
      n1 = fibers[i].node1 - 1;
      n2 = fibers[i].node2 - 1;

      F = lin_spr.getForce(fibers[i]);
      // Define force vector from node1 --> node2 in constitutive equation
      // Forces on node1
      forces[n1].x += F.x;
      forces[n1].y += F.y;
      forces[n1].z += F.z;
      // Forces on node2 = -(Forces on node1)
      forces[n2].x -= F.x;
      forces[n2].y -= F.y;
      forces[n2].z -= F.z;
    }
}

//5................................................................................

void network :: getBoundNodes()
{
  int i; // Loop variable

  for (i=0; i<N_nodes; i++)
    {
      // Check X, Y and Z coordinates of each node
      if (nodes[i].x == x_bound[0]){ nodes[i].node_pos = node :: nX;}
      if (nodes[i].x == x_bound[1]){ nodes[i].node_pos = node :: pX;}
      if (nodes[i].y == y_bound[0]){ nodes[i].node_pos = node :: nY;}
      if (nodes[i].y == y_bound[1]){ nodes[i].node_pos = node :: pY;}
      if (nodes[i].z == z_bound[0]){ nodes[i].node_pos = node :: nZ;}
      if (nodes[i].z == z_bound[1]){ nodes[i].node_pos = node :: pZ;}
    }
}

//6................................................................................

void network :: setBoundary(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)

{
  // Sets the network boundary to the input values given
  // To keep default value / previous value of one axis boundary, exnter min and max
  // of that axis to the same value
  // Example : To just change the X bounds keeping Y and Z unchanged : 
  // setBoundary(xmin, xmax, 0, 0, 0, 0)

  // I have to add code to clip the network if it is bigger than input bounds

  // Set bounds
  if (xmax - xmin != 0){x_bound[0] = xmin; x_bound[1] = xmax;}
  if (ymax - ymin != 0){y_bound[0] = ymin; y_bound[1] = ymax;}
  if (zmax - zmin != 0){z_bound[0] = zmin; z_bound[1] = zmax;}

  // Calculate face areas
  x_area = (y_bound[1] - y_bound[0]) * (z_bound[1] - z_bound[0]);
  y_area = (x_bound[1] - x_bound[0]) * (z_bound[1] - z_bound[0]);
  z_area = (x_bound[1] - x_bound[0]) * (y_bound[1] - y_bound[0]);
}

//7................................................................................

void network :: updateFiberClass()
{
  int i;
  for (i=0; i<N_fibs; i++)
    {
      // Update nodal positions in fiber class from network class
      // I might need to change this sometime later!
 
      fibers[i].n1x = nodes[fibers[i].node1 - 1].x;
      fibers[i].n1y = nodes[fibers[i].node1 - 1].y;
      fibers[i].n1z = nodes[fibers[i].node1 - 1].z;
      fibers[i].n2x = nodes[fibers[i].node2 - 1].x;
      fibers[i].n2y = nodes[fibers[i].node2 - 1].y;
      fibers[i].n2z = nodes[fibers[i].node2 - 1].z;
    }
}

//8................................................................................

void network :: stretchNetwork(vector stretch)
{
  // This function multiplies the nodal coordinates by lambda value given by stretch. Assumes only Max face of each axis moves.
  // Future changes to consider : 
  // Option to move both faces on each axis
  // Move faces through given distance instead of by lambda value

  int i; // Loop variable

  // Check if stretch value is less than equal to zero
  if (stretch.x <= 0 || stretch.y <= 0 || stretch.z <= 0){std::cout << "Error : stretchNetwork\n";return;}

  for (i=0; i<N_nodes; i++)
    {
      // Move (xmin, ymin, zmin) corner to (0, 0, 0) and then stretch all fibers and move corner back
      nodes[i].x = (nodes[i].x - x_bound[0]) * stretch.x + x_bound[0];
      nodes[i].y = (nodes[i].y - y_bound[0]) * stretch.y + y_bound[0];
      nodes[i].z = (nodes[i].z - z_bound[0]) * stretch.z + z_bound[0];
    }
  updateFiberClass(); // Update nodal positions in fibers

}

//9................................................................................

double * network :: getJacobian()
{
  int i, p; // Loop variables
  int n1, n2; // Fiber end nodes
  double *J; // Jacobian matrix pointer
  matrix K; // Stiffness from one fiber
  int max, min;

  J = (double *)calloc(3*N_nodes * 3*N_nodes, sizeof(double)); // Memory allocation

  // Loop over fibers and add resulting Jacobian to proper term in J
  for (i=0; i<N_fibs; i++)
    {
      n1 = fibers[i].node1 - 1; // Converted to 0 - N_nodes-1 numbering
      n2 = fibers[i].node2 - 1;
      max = (n1 > n2) ? 3 * n1 : 3 * n2; // Find larger of the two node numbers
      min = (n1 < n2) ? 3 * n1 : 3 * n2; // Find smaller of the two node numbers

      // Gets stiffness in matrix form from the constitutive equation module
      K = lin_spr.getStiffness(fibers[i]);

      
      // Just defining the upper triangular matrix here. J is symmetric
      J[min+3*N_nodes*max] += K.a11;
      J[min+3*N_nodes*(max+1)] += K.a21;
      J[min+3*N_nodes*(max+2)] += K.a31;
      J[(min+1)+3*N_nodes*max] += K.a12;
      J[(min+2)+3*N_nodes*max] += K.a13;
      J[(min+1)+3*N_nodes*(max+1)] += K.a22;
      J[(min+1)+3*N_nodes*(max+2)] += K.a23;
      J[(min+2)+3*N_nodes*(max+1)] += K.a32;
      J[(min+2)+3*N_nodes*(max+2)] += K.a33;

    }


  int temp = 0;
  // Since J is symmetric lower triangle should be same as upper triangle 
  for (i=0; i<3*N_nodes; i++)
    {
      for (p=i+1; p<3*N_nodes; p++)
  	{
  	  J[p + 3*N_nodes*i] = J[i + 3*N_nodes*p];
  	}
    }

  return (J);
}
