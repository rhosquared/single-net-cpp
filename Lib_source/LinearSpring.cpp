#include <cmath>
#include "../include/equations.h"
#include "../include/vector.h"
#include "../include/fiber.h"


vector LinearSpring :: getForce(fiber fib)
{
  vector force;
  // Force vector defined from node1 --> node2
  force.x = k * (fib.getStretch()-1) * (fib.n2x - fib.n1x)/fib.getLength();
  force.y = k * (fib.getStretch()-1) * (fib.n2y - fib.n1y)/fib.getLength();
  force.z = k * (fib.getStretch()-1) * (fib.n2z - fib.n1z)/fib.getLength();

  return(force);
}


//..............................................................................

// Stiffness

matrix LinearSpring :: getStiffness(fiber fib)
{
  matrix K; // Output matrices with df/d(node1) and df/d(node2)

  double l = fib.getLength();

  // Below terms obtained after differentiating constitutive equation
  double fl = k * (fib.getStretch() - 1)/l;

  double xl = (fib.n2x - fib.n1x)/l;
  double yl = (fib.n2y - fib.n1y)/l;
  double zl = (fib.n2z - fib.n1z)/l;
  // Start df/d(node1)..........
  K.a11 = fl * (xl*xl - 1);

  K.a12 = fl * xl * yl;

  K.a13 = fl * xl * zl;

  K.a21 = K.a12;

  K.a22 = fl * (yl*yl - 1);

  K.a23 = fl * yl * zl;

  K.a31 = K.a13;

  K.a32 = K.a23;

  K.a33 = fl * (zl*zl - 1);
  // end df/d(node1).............
  // df/d(node2) = df/d(node1)

  return (K);
}
