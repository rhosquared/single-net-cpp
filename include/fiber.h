// FIBER.H
// Defines class fiber
// Contains function declarations of all fiber related functions

///..........................................................................///

#pragma once

class fiber
{
 public:

  enum status {dead = 0, alive}; // Possible cases of fiber status

  int node1, node2; // Number of nodes in the global node numbering scheme
  double fib_length, init_length; // Fiber current length and initial length
  double n1x, n1y, n1z; // Node 1 coordinates
  double n2x, n2y, n2z; // Node 2 coordinates
  double fib_lambda; // Fiber stretch
  double fib_radius; // Fiber radius

  status fib_stat;// Fiber status
  int fib_type; // Fiber type


  fiber(); // Constructor function

  // Functions to read fiber length and stretch
  double getLength() const {return fib_length;}
  double getStretch() const {return fib_lambda;}

};

void updateFibLength(fiber * );// Function to update length of fiber
