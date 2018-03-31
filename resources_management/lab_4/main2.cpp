#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <signal.h>

double ln(double x);

int main(int argc, char** argv) {
	int pid = getpid();
	printf("MAIN process %d is running\n", pid);

	double x = 0.0;
	scanf("%lf", &x);
	if (x <= 0.0) {
		printf("Error: Argument should be positive number\n");
		return 0;
	}

	int ch[2];
	pipe(ch);
	int piPid = fork();
	if (piPid == 0) {
		execl("./pi.exe", "pi.exe");
	}
	int expPid = fork();
	if (expPid == 0) {
		execl("./exp.exe", "exp.exe");
	}
	
	int expCh[2];
	int piCh[2];
	pipe(expCh);
	pipe(piCh);
	sleep(1);
	kill(expPid, 1);
	kill(piPid, 1);

	write(expCh[1], &x, sizeof(x));
	double _exp = 0.0;
	read(expCh[2], &_exp, sizeof(_exp));
	double _pi = 0.0;
	read(piCh[2], &_pi, sizeof(_pi));
	
	double f = _exp / (x * sqrt(2.0 * _pi));
	printf("Result: %lf\n", f);

	printf("MAIN process %d finished\n", pid);
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
