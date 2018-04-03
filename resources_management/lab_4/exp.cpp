#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include <string>

/*
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler) {
	if (signum == 1)
		pritnf("lol\n");
}
*/

void handler(int sig) {
	printf("sig is caugth\n");
}

int main(int argc, char** argv) {
	signal(1, handler);
	double x = 0.0;
	read(0, &x, sizeof(x));

	int pid = getpid();
	pause();

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

	write(1, &e, sizeof(e));

	pause();
	_exit(1);
}

