#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

double f(double x);
void exp(double x, FILE* pFile);
double ln(double x);
void pi(double x, FILE* pFile);

int main(int argc, char** argv) {
	int pid = getpid();
	printf("main pid: %d\n", pid);
	FILE* pFile = fopen("temp", "w");
	FILE* p2File = fopen("temp", "r");

	double x = 0.0;
	scanf("%lf", &x);
	if (x <= 0.0) {
		printf("Error: Argument should be positive number\n");
		return 0;
	}

	int expPid = fork();
	if (expPid == 0) {
		exp(-(ln(x) * ln(x)) / 2.0, pFile);
	}
	int piPid = fork();
	if (piPid == 0) {
		pi(x, pFile);
	}

	int entriesReaded = 0;
	int readedPid = 0;
	double readedData = 0.0;
	double _exp = 0;
	double _pi = 0;

	while(entriesReaded != 2) {
		fscanf(p2File, "%d%lf", &readedPid, &readedData);
		if (readedPid != 0) {
			entriesReaded++;
			printf("pid: %d\n", readedPid);
			if (readedPid == expPid) {
				_exp = readedData;
			}
			else {
				_pi = readedData;
			}
			readedPid = 0;
		}
	}
	fclose(pFile);
	fclose(p2File);

	double f = _exp / (x * sqrt(2.0 * _pi));
	printf("Result: %lf\n", f);

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
	printf("Process %d is running\n", pid);

	// Computation.
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

	fprintf(pFile, "%d %lf\n", pid, e);
	fclose(pFile);
	printf("Process %d finished\n", pid);
	_exit(1);
}

void pi(double x, FILE* pFile) {
	int pid = getpid();
	printf("Process %d is running\n", pid);

	// Computation.
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

	double result = c1 * sum;
	
	fprintf(pFile, "%d %lf\n", pid, result);
	fclose(pFile);
	printf("Process %d finished\n", pid);
	_exit(1);
}

double ln(double x) {
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
