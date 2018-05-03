#include <stdio.h>
#include <math.h>

const int n = 4;
const double eps = 0.1;
const int maxIterations = 10000;

bool converge(double *xk, double *xkp)
{
	double norm = 0;
	for (int i = 0; i < n; i++) 
	{
		norm += (xk[i] - xkp[i])*(xk[i] - xkp[i]);
	}
	if (sqrt(norm) >= eps)
		return false;
	return true;
}

void solve(double **a, double *x, double *p, double *b) {
	int nIterations = 0;
	do
	{
		nIterations++;
		for (int i = 0; i < n; i++)
			p[i] = x[i];

		for (int i = 0; i < n; i++)
		{
			double var = 0.0;
			for (int j = 0; j < i; j++)
				var += (a[i][j] * x[j]);
			for (int j = i + 1; j < n; j++)
				var += (a[i][j] * p[j]);
			x[i] = (b[i] - var) / a[i][i];
		}
	} while (!converge(x, p));// && (nIterations < maxIterations));
	printf("Iterations number: %d\n", nIterations);
}

int main() {
	double **a, *x, *p, *b;
	a = new double*[n];
	x = new double[n];
	p = new double[n];
	b = new double[n];

	for (int i = 0; i < n; ++i) {
		a[i] = new double[n];
	}

	for (int i = 0; i < n; ++i) {
		a[i][0] = (double)i + 1;
		a[i][1] = (double)i + 1;
		a[i][2] = (double)i + 1;
		a[i][3] = (double)i + 1;
		b[i] = (double)((i + 1) * 10);
		x[i] = 0.0;
		p[i] = 0.0;
	}
	solve(a, x, p, b);

	for (int i = 0; i < n; ++i) {
		printf("%lf\n", x[i]);
	}
	return 0;
}
