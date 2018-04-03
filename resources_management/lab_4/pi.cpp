#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

#include <string>

void handler(int sig) {
	printf("sig is caugth\n");
}

int main(int argc, char** argv) {
	signal(1, handler);
	int pid = getpid();
	pause();

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
	write(1, &result, sizeof(result));
	
	pause();
	return 0;
	_exit(1);
}

