#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

double f(double x);
void exp(double x, FILE* pFile);
double ln(double x, FILE* pFile);
void pi(double x, FILE* pFile);

int main(int argc, char** argv) {
	int pid = getpid();
	printf("main pid: %d\n", pid);
	FILE* pFile = fopen("temp", "w");
	fpos_t* startPos;
	fgetpos(pFile, startPos);

	double x = 3.0;

	int expPid = fork();
	if (expPid == 0) {
		exp(-(ln(x) * ln(x)) / 2.0, pFile);
	}
	int piPid = fork();
	if (piPid == 0) {
		pi(x, pFile);
	}

	int isFileFormed = 0;
	while(!isFileFormed) {
		// Test if the file is ready.
		//exec("");
		if (pFile != 
	}
	fclose(pFile);

	double _exp;
	double _pi;
	double f = _exp / (x * sqrt(2.0 * _pi));

	return 0;
}

double f(double x) {
	//double ln = ln(x);
	//double exp;
	if (x < 0) {
		return 0.0;
	}
	return 0;
	//return (1.0/2.0) * exp(-(1.0/2.0) * ln(x) * ln(x)) / (x * sqrt(2.0 * pi()));
}

void exp(double x, FILE* pFile) {
	int pid = getpid();
	printf("hi %d\n", pid);
	double exp = 15.0;

	fprintf(pFile, "%d\n", pid);
	_exit(1);

	double xExp = 1.0;
	int factorial = 1;
	double e = 0.0;

	// Iterations number choosen due to
	// range of integer type (factorial must 
	// fit into integer one).
	int nIterations = 12;
	for (int i = 1; i < nIterations; ++i) {
		e += (xExp / (double)factorial);
		xExp *= x;
		factorial *= i;
	}
//	return e;
}

double ln(double x, FILE* pFile) {
	double y = (x - 1.0) / (1.0 + x);
	int c1 = 1;
	double yExp = 1;
	double sum = 0.0;

	int nIterations = 100;
	for (int i = 0; i < nIterations; ++i) {
		double c2 = 1.0 / c1;
		sum += yExp * c2;

		c1 += 2;
		yExp *= y;
		yExp *= y;
	}

	return 2.0 * y * sum;
}

void pi(double x, FILE* pFile) {
	int pid = getpid();
	printf("hi %d\n", pid);
	fprintf(pFile, "%d\n", 15);
	_exit(1);

	double c1 = (double)sqrt(12);
	double c2 = -1.0/ 3.0;
	double sum = 0;
	double c2Exp = 1;

	// After 40 iterations method reaching max
	// precision due to machine arithmetic error.
	int nIterations = 40;
	for (int i = 0; i < nIterations; ++i) {
		sum += c2Exp / (2 * i + 1);
		c2Exp *= c2;
	}

	//return c1 * sum;
}
