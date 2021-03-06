// This is the header file for SingleNet.cpp

#pragma once

#include <iostream>
#include <cstring>
#include "network.h"
#include "vector.h"

int SparseTriplet(int flag, int N, double *A, int *ia, int *ja, double *Annz);

double *vector2array(vector *A, int N);

void DisplayMsg(const string msgtype, const string msg);
