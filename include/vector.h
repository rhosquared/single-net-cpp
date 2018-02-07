// VECTOR.H
// Defines class vector and tensor

///..........................................................................///

#pragma once
#include <cmath>

class vector
{
 public :

  double x, y, z; // X, Y and Z components of vector

  vector(){x = 0; y = 0; z = 0;} // Constructor function


  double getMagnitude() const {return sqrt(x*x + y*y + z*z );} // Get vector norm
};

class matrix
{
 public : 

  double a11, a12, a13; // Rows of the matrix
  double a21, a22, a23;
  double a31, a32, a33;

  matrix(){a11 = a12 = a13 = a21 = a22 = a23 = a31 = a32 = a33 = 0;} // Constructor function

  double getDeterminant()
  {
    return (a11*(a22*a33 - a32*a23) - a12*(a21*a33 - a31*a23) + a13*(a21*a32 - a31*a22));
  }
};
