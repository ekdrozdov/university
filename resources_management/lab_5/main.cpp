#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void p1(int fd1[2], int fd2[2]);
void p2(int fd[2]);
void handler(int sig);

int main() {
	int myPid = getpid();
	printf("%d: (P0) started\n", myPid);

	int fd1[2];

	printf("%d: Creating channels\n", myPid);
	if (pipe(fd1) == -1) {
		perror("pipe");
		_exit(EXIT_FAILURE);
	}

	int fd2[2];
	if (pipe(fd2) == -1) {
		perror("pipe");
		_exit(EXIT_FAILURE);
	}

	printf("%d: Creating P1\n", myPid);
	int p1Pid = fork();
	if (p1Pid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (p1Pid == 0) {
		p1(fd1, fd2);
	}

	printf("%d: Handling data from channels\n", myPid);
	char pid[5];
	char message[40];
	read(fd1[0], &pid, sizeof(pid));
	read(fd1[0], &message, sizeof(message));
	printf("%d: Readed: %s: %s\n", myPid, pid, message);

	read(fd1[0], &pid, sizeof(pid));
	read(fd1[0], &message, sizeof(message));
	printf("%d: Readed: %s: %s\n", myPid, pid, message);

	printf("%d: Waiting for childs to finish\n", myPid);
	int wstatus;
	wait(&wstatus);
	printf("%d: Child terminated with status %d\n", myPid, wstatus);
	wait(&wstatus);
	printf("%d: Child terminated with status %d\n", myPid, wstatus);

	printf("%d: (P0) finished\n", myPid);
	return 0;
}

void handler(int sig) {
	printf("%d: signal caught\n", getpid());
}

void p1(int fd1[2], int fd2[2]) {
	signal(1, handler);
	int myPid = getpid();
	printf("%d: (P1) started\n", myPid);
	printf("%d: Creating P2\n", myPid);
	int p2Pid = fork();
	if (p2Pid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (p2Pid == 0) {
		p2(fd2);
	}

	char pid[5];
	sprintf(pid, "%d", myPid);
	char message[40] = "Hello, my name is P1";
	printf("%d: Writing in channel\n", myPid);
	write(fd1[1], &pid, sizeof(pid));
	write(fd1[1], &message, sizeof(message));

	sleep(1);
	printf("%d: Sending signal to %d\n", myPid, p2Pid);
	kill(p2Pid, 1);

	printf("%d: Waiting for a signal\n", myPid);
	pause();

	printf("%d: Reading from channel\n", myPid);
	read(fd2[0], &pid, sizeof(pid));
	read(fd2[0], &message, sizeof(message));
	sprintf(message, "%s [handled by P1]", message);

	printf("%d: Writing in channel\n", myPid);
	write(fd1[1], &pid, sizeof(pid));
	write(fd1[1], &message, sizeof(message));

	printf("%d: (P1) finished\n", myPid);
	_exit(EXIT_SUCCESS);
}

void p2(int fd[2]) {
	signal(1, handler);
	int myPid = getpid();
	printf("%d: (P2) started\n", myPid);

	printf("%d: Waiting for a signal\n", myPid);
	pause();

	char pid[5];
	sprintf(pid, "%d", myPid);
	char message[40] = "Hello, my name is P2";
	printf("%d: Writing in channel\n", myPid);
	write(fd[1], &pid, sizeof(pid));
	write(fd[1], &message, sizeof(message));

	sleep(1);
	printf("%d: Sending signal to %d\n", myPid, getppid());
	kill(getppid(), 1);
	printf("%d: (P2) finished\n", myPid);
	_exit(EXIT_SUCCESS);
}
