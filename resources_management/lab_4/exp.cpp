#include <unistd.h>
#include <stdio.h>
#include <signal.h>

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

int main() {
	signal(1, handler);
	int ch[2];
	pipe(ch);
	double x = 0.0;
	read(ch[2], &x, sizeof(x));

	int pid = getpid();
	printf("Process %d is running\n", pid);
	pause();
	printf("Process %d woke up\n", pid);

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

	write(ch[1], &e, sizeof(e));

	printf("Process %d finished\n", pid);
	pause();
	_exit(1);
}

