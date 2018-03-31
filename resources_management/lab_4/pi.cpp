#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig) {
	printf("sig is caugth\n");
}

int main() {
	signal(1, handler);
	int pid = getpid();
	printf("Process %d is running\n", pid);
	pause();
	printf("Process %d woke up\n", pid);

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
	int ch[2];
	pipe(ch);
	write(ch[1], &result, sizeof(result));
	
	printf("Process %d finished\n", pid);
	pause();
	return 0;
	_exit(1);
}

