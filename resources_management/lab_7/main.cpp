#include <sys/wait.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

/* Notes
 * flag 0666 means make queue read and appendable by all.
 */

const int MSGSZ = 128;
const int TBLSZ = 100;

typedef struct _msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} Message;

void printUsage(char* programName);
int createChild(key_t key);
void runChildProcess(key_t key);

int main(int argc, char** argv) {
	if (argc < 2) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}
	int myPid = getpid();
	int childsAmount = 0;
	sscanf(argv[1], "%d", &childsAmount);

	// Create a message queue.
	key_t key = 1;
	int msgqid = msgget(key, IPC_CREAT | 0666);
	if (msgqid < 0) {
		perror("msgget");
		_exit(EXIT_FAILURE);
	}

	// Create table.
	int table[TBLSZ];
	for (int i = 0; i < TBLSZ; ++i) {
		table[TBLSZ] = i * i;
	}

	// Create K (declared as a 'childsAmount') processes.
	int* childPids = new int[childsAmount];
	for (int i = 0; i < childsAmount; ++i) {
		childPids[i] = createChild(key);
	}

	Message message;
	// Try to recieve a message.
	if (msgrcv(msgqid, &message, MSGSZ, message.mtype, 0) < 0) {
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("%d: Recieved message: %s\n", myPid, message.mtext);

	for (int i = 0; i < childsAmount; ++i) {
		if (msgrcv(msgqid, &message, MSGSZ, myPid, 0) < 0) {
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}

		// Handle request specified in recieved message.
		int oldVal = handler();
		df

		printf("%d: Recieved message: %s\n", myPid, message.mtext);
	}

	msgctl(msgqid, IPC_RMID, NULL);

	return EXIT_SUCCESS;
}

int createChild(key_t key) {
	int childPid = fork();
	if (childPid == -1) {
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	if (childPid == 0) {
		runChildProcess(key);
		_exit(EXIT_SUCCESS);
	}
	return childPid;
}

void runChildProcess(key_t key) {
	int myPid = getpid();
	printf("%d: start\n", myPid);

	// Try to access message queue.
	int msgqid = msgget(key, 0666);
	if (msgqid < 0) {
		perror("msgget");
		_exit(EXIT_FAILURE);
	}

	// Create a message.
	Message message;
	message.mtype = 1;
	if (sprintf(message.mtext, "i'm %d", myPid) < 0) {
		perror("sprintf");
		_exit(EXIT_FAILURE);
	}

	// Try to pass message into a message queue.
	if (msgsnd(msgqid, &message, MSGSZ, IPC_NOWAIT) < 0) {
		perror("msgsnd");
		_exit(EXIT_FAILURE);
	}

	printf("%d: Passed message: %s\n", myPid, message.mtext);

	if (msgrcv(msgqid, &message, MSGSZ, message.mtype, 0) < 0) {
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("%d: Recieved message: %s\n", myPid, message.mtext);
}

void printUsage(char* programName) {
	printf("Usage:\n");
	printf("%s [childs amount]\n", programName);
}
