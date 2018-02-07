// This file contains general functions for the Single Network code
// The following functions are defined here:
// 1. SparseTriplet(int N, double *A, int *ia, int *ja, double *Annz)
// 2. vector2array(vector A)
// 3. DisplayMsg(string msgtype, string msg)

///.........................................................................///

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "../include/SingleNet.h"
#include "../include/mgmres.h"
#include "../include/network.h"
#include "../include/vector.h"

//1............................................................................

int SparseTriplet(int flag, int N, double *A, int *ia, int *ja, double *Annz)
{
  // This function converts a given matrix into a sparse triplet form
  // This function has to be called twice. Once with flag 1 to return NNZ and
  // with flag 0 to return ia, ja and Annz
  // Function arguments:
  // Input, flag, 1 returns NNZ, 0 returns ia, ja and Annz. Use 1 before 0
  // Input, N, order of system
  // Input, A, matrix to be changed to ST form
  // Output, nnz, number of non zero elements of A
  // Outputs, ia[nnz], ja[nnz], row and column indices of non zero elements of A
  // NOTE: Indices start from 0 and not 1
  // Output, Annz[nnz], array of non zero values of A

  // Returns nnz if succesfull or -1 for error

  using namespace std;

  int i, j; // Loop variables

  // Find nnz
  int nnz = 0;

  for (i=0;i<N;i++)
    {
      for (j=0;j<N;j++)
	{
	  if (A[i + N*j] != 0)
	    {
	      nnz++;
	    }
	}
    }
  if (flag == 1){return(nnz);}

  // Get ia, ja and Annz

  int count = 0;

  for (i=0;i<N;i++)
    {
      for (j=0;j<N;j++)
	{
	  if (A[i + N*j] != 0)
	    {
	      ia[count] = i;
	      ja[count] = j;
	      Annz[count] = A[i + N*j];
	      count++;
	    }
	}
    }
  if (count != nnz){cout << "SparseTriplet : Error" << endl; return(-1);}
  return(nnz); // All done
}

//2.............................................................................

double *vector2array(vector *A, int N)
{
  // This function changes an object of class vector into a array of doubles
  // with values in the order x,y,z
  // Function arguments:
  // Input, A, array of vectors
  // Input, N, size of vector array A

  using namespace std;

  int i; // Loop variable
  double *arr;

  // Memory allocation and check
  arr = (double *)calloc(3 * N, sizeof(double));
  if (arr == NULL){cout << "vector2array : Error in memory allocation" << endl;}

  for (i=0; i<N; i++)
    {
      arr[3*i] = A[i].x;
      arr[3*i + 1] = A[i].y;
      arr[3*i + 2] = A[i].z;
    }


  return(arr); // All done
}

//3.............................................................................

void DisplayMsg(const string msgtype, const string msg)
{

  using namespace std;
  // This function when called displays the given message in the required message classifier e.g error or warning
  int k;

  // Option 1: Display starting message
  k = strcmp("start", msgtype.c_str());
  if (k == 0)
    {
      cout << "******************************" << endl;
      cout << "******************************" << endl;
      cout << "SINGLE NETWORK STRETCH CODE" << endl;
      cout << "Version : 1.0" << endl;
      cout << "RD" << endl;
      cout << "******************************" << endl;
      cout << endl;
      return;
    }

  // Option 2: Display error message
  k = strcmp("error", msgtype.c_str());
  if (k == 0)
    {
      cout << "******************************" << endl;
      cout << "           ERROR:             " << endl;
      cout << msg << endl;
      cout << "Terminating run" << endl;
      cout << "******************************" << endl;
      return;

    }

  // Option 3: Display warnings
  k = strcmp("warning", msgtype.c_str());
    if (k == 0)
      {
	cout << "******************************" << endl;
	cout << "         WARNING:             " << endl;
	cout << msg << endl;
	cout << "******************************" << endl;
	return;
      }
}
