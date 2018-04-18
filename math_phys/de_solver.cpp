#include "de_solver.h"

DESolver::DESolver(Domain domain, DE2O* task) {
	int oxNodesTotal = domain.ox.back() - domain.ox.front() + 1;
	int oyNodesTotal = domain.oy.back() - domain.oy.front() + 1;
	diagonalsDistanse = oxNodesTotal - 2;
	int nodesTotal = oxNodesTotal * oyNodesTotal;
	matrixHeight = nodesTotal;

	A = new double*[nodesTotal];
	b = new double[nodesTotal];
	x = new double[nodesTotal];
	for (int i = 0; i < nodesTotal; ++i) {
		b[i] = 0.0;
		x[i] = 0.0;
		A[i] = new double[nLayoutPoints];
		for (int j = 0; j < nLayoutPoints; ++j) {
			A[i][j] = 0.0;
		}
	}

	// Consider links.
	lambda = task->lambda;
	gamma = task->gamma;
	double x = domain.ox.front();
	double y = domain.oy.front();
	double step = 1.0;
	for (int i = 0; i < nodesTotal; ++i) {
		double hx = 1;
		double hy = 1;
		double hx2 = hx * hx;
		double hy2 = hy * hy;
		// Bottom link.
		A[i][0] = -lambda / hy2;
		// Left link.
		A[i][1] = -lambda / hx2;
		// Self link.
		A[i][2] = 2 * lambda * ((1.0 / hx2) + (1.0 / hy2)) + gamma;
		// Right link.
		A[i][3] = -lambda / hx2;
		// Top link.
		A[i][4] = -lambda / hy2;
		// Right part.
		b[i] = task->f(x, y);
		x += step;
		y += step; //!.
	}

	// Consider fake nulls (caused by diagonal storage format).
	int shift = oxNodesTotal;
	for (int i = 0; i < shift; ++i) {
		A[i][0] = 0.0;
		A[nodesTotal - i - 1][4] = 0.0;
	}
	A[0][1] = 0.0;
	A[nodesTotal - 1][3] = 0.0;

	// Consider broken links.
	for (int i = shift - 1; i < nodesTotal; i += shift) {
		A[i][3] = 0.0;
		if (i != (nodesTotal - 1)) {
			A[i + 1][1] = 0.0;
		}
	}

	// Consider boundary conditions.
	x = domain.ox.front();
	y = domain.oy.front();
	int iNode = 0;
	for (y = domain.oy.front(); y <= domain.oy.back(); y += step) {
		for (x = domain.ox.front(); x <= domain.ox.back(); x += step, iNode++) {
			// Bound #1.
			if (x == domain.ox[0]) {
				if (task->boundaryConditions[0] == 1) {
					A[iNode][0] = 0.0;
					A[iNode][1] = 0.0;
					A[iNode][2] = 1.0;
					A[iNode][3] = 0.0;
					A[iNode][4] = 0.0;
				}
				else if (task->boundaryConditions[0] == 2) {
					A[iNode][2] = lambda / step; // xStep
					A[iNode][3] = -lambda / step;
					b[iNode] = -task->teta(x, y);
				}
			}
			// Bound #2.
			if (y == domain.oy[2]) {
				if (task->boundaryConditions[1] == 1) {
					A[iNode][0] = 0.0;
					A[iNode][1] = 0.0;
					A[iNode][2] = 1.0;
					A[iNode][3] = 0.0;
					A[iNode][4] = 0.0;
				}
				else if (task->boundaryConditions[1] == 2) {
					A[iNode][2] = lambda / step; // yStep
					A[iNode][3] = -lambda / step;
					b[iNode] = task->teta(x, y);
				}
			}
			// Bound #3.
			if ((x == domain.ox[1]) && (y >= domain.oy[1])) {
				if (task->boundaryConditions[2] == 1) {
					A[iNode][0] = 0.0;
					A[iNode][1] = 0.0;
					A[iNode][2] = 1.0;
					A[iNode][3] = 0.0;
					A[iNode][4] = 0.0;
				}
				else if (task->boundaryConditions[2] == 2) {
					A[iNode][2] = lambda / step; // xStep
					A[iNode][3] = -lambda / step;
					b[iNode] = task->teta(x, y);
				}
			}
			// Bound #4.
			if ((x >= domain.ox[1]) && (y == domain.oy[1])) {
				if (task->boundaryConditions[3] == 1) {
					A[iNode][0] = 0.0;
					A[iNode][1] = 0.0;
					A[iNode][2] = 1.0;
					A[iNode][3] = 0.0;
					A[iNode][4] = 0.0;
				}
				else if (task->boundaryConditions[3] == 2) {
					A[iNode][2] = lambda / step; // yStep
					A[iNode][3] = -lambda / step;
					b[iNode] = task->teta(x, y);
				}
			}
			// Bound #5.
			if (x == domain.ox[2]) {
				if (task->boundaryConditions[4] == 1) {
					A[iNode][0] = 0.0;
					A[iNode][1] = 0.0;
					A[iNode][2] = 1.0;
					A[iNode][3] = 0.0;
					A[iNode][4] = 0.0;
				}
				else if (task->boundaryConditions[4] == 2) {
					A[iNode][2] = lambda / step; // xStep
					A[iNode][3] = -lambda / step;
					b[iNode] = task->teta(x, y);
				}
			}
			// Bound #6.
			if (y == domain.oy[0]) {
				if (task->boundaryConditions[5] == 1) {
					A[iNode][0] = 0.0;
					A[iNode][1] = 0.0;
					A[iNode][2] = 1.0;
					A[iNode][3] = 0.0;
					A[iNode][4] = 0.0;
				}
				else if (task->boundaryConditions[5] == 2) {
					A[iNode][2] = lambda / step; // yStep
					A[iNode][3] = -lambda / step;
					b[iNode] = -task->teta(x, y);
				}
			}
		}
	}

	// Consider fake nodes.
	iNode = 0;
	for (y = domain.oy.front(); y <= domain.oy.back(); y += step) {
		for (x = domain.ox.front(); x <= domain.ox.back(); x += step, iNode++) {
			if ((x > domain.ox[1]) && (y > domain.oy[1])) {
				A[iNode][0] = 0.0;
				A[iNode][1] = 0.0;
				A[iNode][2] = 1.0;
				A[iNode][3] = 0.0;
				A[iNode][4] = 0.0;
				b[iNode] = 0.0;
			}
		}
	}	
}
 
DESolver::~DESolver() {
	if (A != NULL) {
		for (int i = 0; i < matrixHeight; ++i) {
			delete[] A[i];
		}
		delete[] A;
	}
	if (x != NULL) {
		delete[] x;
	}
	if (b != NULL) {
		delete[] b;
	}
	if (task != NULL) {
		delete task;
	}
}

void DESolver::solve() {
	slaeSolver.SetData(matrixHeight, diagonalsDistanse, b, A);
	x = slaeSolver.Resh();
}

void DESolver::printInfo(std::vector<double> ox, std::vector<double> oy) {
	printf("Matirx A (diagonal format):\n");
	int nLayoutPoints = 5;
	// Let's assume that vectors contain two components and step is 1.

	for (int i = 0; i < matrixHeight; ++i) {
		printf("[%i]\t ", i);
		for (int j = 0; j < nLayoutPoints; ++j) {
			printf("%.1lf\t", A[i][j]);
			//std::cout << A[i][j];
		}
		printf("\n");
	}

	printf("Vector x:\n");
	for (int i = 0; i < matrixHeight; ++i) {
		printf("[%i]\t ", i);
		printf("%.1lf\n", x[i]);
	}
	printf("Vector b:\n");
	for (int i = 0; i < matrixHeight; ++i) {
		printf("[%i]\t ", i);
		printf("%.1lf\n", b[i]);
	}
}