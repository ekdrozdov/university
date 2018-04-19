#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// stdin = 0
// stdout = 1
// stderr = 2

// fd[0] -- read
// fdp[1] -- write

/*
 * Program scenario:
 * ls -la > a.txt & ps > b.txt; cat a.txt b.txt | sort
 *
 */

int main() {
	int out = dup(1);
	int s_in = dup(0);
	printf("Main started\n");
	int fd;

	printf("Executing 'ls -la'\n");
	// Execute "ls -la" with an "a.txt" as an output stream.
	fd = open("a.txt", O_WRONLY | O_CREAT);
	close(1);
	fcntl(fd, F_DUPFD, 1);
	int lsPid = fork();
	if (lsPid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (lsPid == 0) {
		execlp("ls", "ls", "-la");
		_exit(EXIT_SUCCESS);
	}

	dup2(out, 1);
	printf("Executing 'ps'\n");
	// Execute "ps" with a "b.txt" as an output stream.
	fd = open("b.txt", O_WRONLY | O_CREAT);
	close(1);
	fcntl(fd, F_DUPFD, 1);
	int psPid = fork();
	if (psPid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (psPid == 0) {
		execlp("ps", "ps");
		_exit(EXIT_SUCCESS);
	}

	dup2(out, 1);
	printf("Waiting for childs to finish\n");
	// Waiting for childs to finish.
	wait(NULL);
	wait(NULL);

	printf("Executing 'cat'\n");
	// Execute "cat a.txt b.txt" and pass result to
	// "sort" via pipe "fd2".
	int fd2[2];
	pipe(fd2);
	close(1);
	fcntl(fd2[1], F_DUPFD, 1);
	int catPid = fork();
	if (catPid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (catPid == 0) {
		execlp("cat", "cat", "a.txt");
		_exit(EXIT_SUCCESS);
	}

	//printf("Cat result: %s\n", fd2[1]);
	dup2(out, 1);
	printf("Waiting for childs to finish\n");
	// Wait for a "cat" to finish due to pipe mechanic.
	wait(NULL);

	char buff[512];
	read(fd2[0], &buff, sizeof(buff));
	printf("Pipe content:\n%s\n", buff);
	write(fd2[1], &buff, sizeof(buff));

	printf("Executing sort\n");
	// Execute "sort" with "cat" output as an input stream
	// and standart output as an output stream.
	close(0);
	fcntl(fd2[0], F_DUPFD, 0);
	close(1);
	dup2(out, 1);
	int sortPid = fork();
	if (sortPid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (sortPid == 0) {
		execlp("sort", "sort", 0);
		_exit(EXIT_SUCCESS);
	}

	dup2(out, 1);
	printf("Main finished\n");

	return 0;
}

/*
int fd, fd2; 
fd = open("aa.txt", O_RDONLY); 
close(0); 
fcntl(fd,F_DUPFD,0); 
fd = open("bb.txt", O_WRONLY | O_CREAT); 
close(1); 
fcntl(fd2, F_DUPFD, 1); 
execlp("prog", "prog", 0);
*/

/*
	int fd0;
	// Replace stdin.
	fd[0] = open("a.txt", O_RDONLY | O_CREAT);
	close(0);
	//fcntl(fd[0], F_DUPFD, 0);
	dup(fd[0]);
	*/

	/*
	// Replace stdout.
	int fd1;
	fd1 = open("b.txt", 'w');
	close(1);
	//fcntl(fd[1], F_DUPFD, 1);
	dup2(fd1, 1);
	printf("hi");
	//execlp("ls", "ls", 0);
	//close(fd[1]);
	*/

