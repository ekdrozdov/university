#pragma once
#include <cstddef>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "de2o.h"
#include "domain.h"
#include "gauss_zeidel.h"

/*
Bound numbers in shape:
-----------------------
	 2
	+--+
	|  | 3
	|  |     4
1	|  +_______+
	|          | 5
	+----------+
		6
-----------------------
*/


class DESolver {
public:
	DESolver(Domain domain, DE2O* task);
	~DESolver();

	void init();

	//buildMatrixA(layout);
	void solve();

	//void buildSLAE(std::vector<double> ox, std::vector<double> oy);
	void printInfo(std::vector<double> ox, std::vector<double> oy);

private:
	GaussZeidel slaeSolver;
	static const int nLayoutPoints = 5;
	DE2O* task;
	double** A;
	double* x;
	double* b;
	double gamma;
	double lambda;
	int matrixHeight;
	int diagonalsDistanse;
};
