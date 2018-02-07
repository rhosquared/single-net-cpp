#include <iostream>
#include <fstream>
#include <cstdlib>
#include "include/fiber.h"
#include "include/network.h"
#include "include/vector.h"
#include "include/equations.h"
#include "include/SingleNet.h"
#include "include/mgmres.h"

using namespace std;

int main()
{
  // double a, b,c;
  // double *nodes;
  // int i, j;
  // ifstream infile;
  // string filename;

  // fiber *F;

  // F = (fiber *)calloc(10, sizeof(fiber));

  // filename = "net_1.del";

  // infile.open(filename.c_str());

  // infile >> a >> b >> c;

  // nodes = (double *) calloc(20 , sizeof(double));

  // for(i=0; i<20; i++)
  //   {
  //     infile >> nodes[i];
  //   }

  // infile.close();

  // cout << a << b << c << endl;
  // cout << endl;
  // cout << "Nodes array is : "<< endl;
  // for(i=0;i<2;i++)
  //   {
  //     for(j=0;j<10;j++)
  // 	{
  // 	  cout << nodes[10*i + j];
  // 	}
  //     cout << endl;
  //   }
  // cout << endl;

  DisplayMsg("start", "NA");
  network Net;
  vector f;
  double *J;
  f.x = 1.5;
  f.y = 1;
  f.z = 1;

  Net.readNetwork( "net_1.del" );

  std::cout << Net.N_fibs << "  " << Net.N_nodes << std::endl;
 
  Net.updateNetwork();
  std::cout << Net.fibers[0].getLength() << std::endl;

  Net.getFibForces();
  DisplayMsg("warning", "Network not stretched\nApply stretchNetwork()");
  std::cout << "Force 5(1) : " << Net.forces[5].getMagnitude() << std::endl;

  Net.stretchNetwork(f);

  Net.getFibForces();

  std::cout << "Force 5(2) : " <<  Net.forces[5].getMagnitude() << std::endl;
  std::cout << Net.forces[5].x << "i + "<<Net.forces[5].y<<"j"<< std::endl;


  // std::cout << Net.fibers[0].node1 << "  " << Net.fibers[0].node2 << std::endl;
  J = Net.getJacobian();

  // J = (double *)calloc(5*5, sizeof(double));

  // J[0] = 10.34; J[6] = 2.34; J[12] = -9.87; J[18] = 21.32; J[24] = -1.34;
  // J[10] = -9.45; J[2] = -9.45; J[17] = -7.4; J[13] = -7.4;

  std::cout << "Size of forces = " << Net.N_nodes << std::endl;

  std::cout << "---------------------------\n";

  double *x, *xold;
  double *RHS;
  int i;
  int *ia;
  int *ja;
  double *Annz;
  int p, q;


  x = (double *)calloc(3*Net.N_nodes, sizeof(double));
  x[1] = 1; x[400] = 2; x[123] = 1;
  xold = (double *)calloc(3*Net.N_nodes, sizeof(double));

  RHS = vector2array(Net.forces, Net.N_nodes);


  int nnz = SparseTriplet(1, 3*Net.N_nodes, J, ia, ja, Annz);

  // std::cout << "nnz = " << nnz << std::endl;
  Annz = (double *)calloc(nnz, sizeof(double));
  ia = (int *)calloc(nnz, sizeof(int));
  ja = (int *)calloc(nnz, sizeof(int));

  nnz = SparseTriplet(0, 3*Net.N_nodes, J, ia, ja, Annz);

  // Write J and RHS to text files

  ofstream outf1, outf2;

  outf1.open("Jacobian.txt");

  {
    for (p = 0; p < 3*Net.N_nodes; p++)
	{
	  for (q = 0; q < 3*Net.N_nodes; q++)
	    {
	      outf1 << J[p +3* q* Net.N_nodes] << ", ";
	    }
	  outf1 << "\n";
	}
    }
    outf1.close();
    outf2.open("RHS.txt");

      for (p = 0; p < 3*Net.N_nodes; p++)
	{
	  outf2 << RHS[p]<< "\n";
	} 
    outf2.close();

  mgmres_st(3*Net.N_nodes, nnz, ia, ja, Annz, x, RHS, 1335, 20, 1e-10, 1e-12);

  std::cout << "x[5] = " << x[1] << std::endl;
  std::cout << "x[100] = " << x[2] << std::endl;

  ofstream outf3;

  outf3.open("Solution.txt");

  for (p = 0; p < 3*Net.N_nodes; p++)
    {
      outf3 << x[p] << "\n";
    }

  outf3.close();

  std::cout << "All good!" << std::endl;
}
