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

	int fdPi[2];
	pipe(fdPi);
	
	int piPid = fork();
	if (piPid == 0) {
		dup2(fdPi[1], 1);
		execl("./pi.exe", "pi.exe");
	}

	int fdExp[2];
	pipe(fdExp);
	double expArg = (-(ln(x) * ln(x)) / 2);
	write(fdExp[1], &expArg, sizeof(x));

	int expPid = fork();
	if (expPid == 0) {
		dup2(fdExp[0], 0);
		dup2(fdExp[1], 1);
		execl("./exp.exe", "exp.exe");
	}
	
	sleep(1);
	kill(expPid, 1);
	kill(piPid, 1);
	sleep(1);

	double _exp = 0.0;
	read(fdExp[0], &_exp, sizeof(_exp));
	double _pi = 0.0;
	read(fdPi[0], &_pi, sizeof(_pi));
	
	printf("exp = %lf\n", _exp);
	printf("pi = %lf\n", _pi);
	double f = _exp / (x * sqrt(2.0 * _pi));
	printf("Result: %lf\n", f);

	printf("MAIN process %d finished\n", pid);
	return 0;
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
