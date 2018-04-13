#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd0[2];
	if (pipe(fd0) == -1) {
		perror("pipe");
		_exit(EXIT_FAILURE);
	}

	int fd1[2];
	if (pipe(fd1) == -1) {
		perror("pipe");
		_exit(EXIT_FAILURE);
	}

	int fd2[2];
	if (pipe(fd2) == -1) {
		perror("pipe");
		_exit(EXIT_FAILURE);
	}

	int p1Pid = fork();
	if (p1Pid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (p1Pid == 0) {
		// Child routine.

		int p3Pid = fork();
		if (p3Pid == -1) {
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		if (p3Pid == 0) {
			// Child routine.
		}
	}

	int p2Pid = fork();
	if (p2Pid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (p2Pid == 0) {
		// Child routine.
	}
	
	return 0;
}
