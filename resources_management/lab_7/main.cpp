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
const int TBLSZ = 10;

typedef struct _msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} Message;

void printUsage(char* programName);
int createChild(key_t key);
void runChildProcess(key_t key);
void printTable(int* pTable, int tableSize);

int main(int argc, char** argv) {
	if (argc < 2) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}
	int myPid = getpid();
	printf("%d: Parent started\n", myPid);
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
		table[i] = i * i;
	}

	printf("Table content:\n");
	printTable(table, TBLSZ);

	// Create K (declared as a 'childsAmount') processes.
	int* childPids = new int[childsAmount];
	for (int i = 0; i < childsAmount; ++i) {
		childPids[i] = createChild(key);
	}

	// Try to recieve a message.
	Message message;
	printf("childs %d\n", childsAmount);
	for (int i = 0; i < childsAmount; ++i) {
		// Get message from queue.
		printf("i =  %d\n", i);
		if (msgrcv(msgqid, &message, MSGSZ, myPid, 0) < 0) {
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		printf("%d: Recieved message: %s\n", myPid, message.mtext);

		// Handle request specified in recieved message.
		int destPid, strNumber, newVal;
		sscanf(message.mtext, "%d%d%d", &destPid, &strNumber, &newVal);
		int oldVal = table[strNumber];
		table[strNumber] = newVal;

		// Build a message with old value of the table element.
		message.mtype = destPid;
		if (sprintf(message.mtext, "%d", oldVal) < 0) {
			perror("sprintf");
			_exit(EXIT_FAILURE);
		}

		// Feedback to childs.
		if (msgsnd(msgqid, &message, MSGSZ, IPC_NOWAIT) < 0) {
			perror("msgsnd");
			_exit(EXIT_FAILURE);
		}
	}

	printf("Table content:\n");
	printTable(table, TBLSZ);

	// Waiting for childs to finish.
	for (int i = 0; i < childsAmount; ++i) {
		wait(NULL);
	}
	msgctl(msgqid, IPC_RMID, NULL);
	printf("%d: Parent finished\n", myPid);

	return EXIT_SUCCESS;
}

void printTable(int* pTable, int tableSize) {
	for (int i = 0; i < tableSize; ++i) {
		printf("%d\n", pTable[i]);
	}
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
	printf("%d: Child started\n", myPid);

	// Try to access message queue.
	int msgqid = msgget(key, 0666);
	if (msgqid < 0) {
		perror("msgget");
		_exit(EXIT_FAILURE);
	}

	// Build a message.
	Message message;
	message.mtype = getppid();
	if (sprintf(message.mtext, "%d %d %d", 
				myPid, myPid % TBLSZ, myPid) < 0) {
		perror("sprintf");
		_exit(EXIT_FAILURE);
	}

	// Try to pass message into a message queue.
	if (msgsnd(msgqid, &message, MSGSZ, IPC_NOWAIT) < 0) {
		perror("msgsnd");
		_exit(EXIT_FAILURE);
	}

	printf("%d: Passed message: %s\n", myPid, message.mtext);

	// Try to recieve message with an old value.
	message.mtype = myPid;
	if (msgrcv(msgqid, &message, MSGSZ, message.mtype, 0) < 0) {
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("%d: Recieved message (old value): %s\n", myPid, message.mtext);
	printf("%d: Child finished\n", myPid);
	_exit(EXIT_SUCCESS);
}

void printUsage(char* programName) {
	printf("Usage:\n");
	printf("%s [childs amount]\n", programName);
}
