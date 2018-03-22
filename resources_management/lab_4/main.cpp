#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

double f(double x);
void exp(double x, FILE* pFile);
void ln(double x, FILE* pFile);
void pi(double x, FILE* pFile);

int main(int argc, char** argv) {
	int pid = getpid();
	printf("main pid: %d\n", pid);
	int* status;
	FILE* pFile = fopen("temp", "w");

	double x = 2;

	if (fork() == 0) {
		exp(x, pFile);
	}
	if (fork() == 0) {
		pi(x, pFile);
	}
	if (fork() == 0) {
		ln(x, pFile);
	}
	fclose(pFile);
	//while(cond) {
	//}

	//fscanf();

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
}

void ln(double x, FILE* pFile) {
	int pid = getpid();
	printf("hi %d\n", pid);
	fprintf(pFile, "%d\n", pid);
	_exit(1);
}

void pi(double x, FILE* pFile) {
	int pid = getpid();
	printf("hi %d\n", pid);
	fprintf(pFile, "%d\n", pid);
	_exit(1);
}
