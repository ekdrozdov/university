#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char** argv) {
	// Create socket.
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock < 0) {
		perror("bind failed");
		return EXIT_FAILURE;
	}
	printf("Socket created\n");

	// Connection request.
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Connection request\n");
	if (connect(serv_sock, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) {
		perror("connection failed");
		return EXIT_FAILURE;
	}

	const char* text = "Hello";
	printf("Send text '%s'\n", text);
	send(serv_sock, text, sizeof(text), 0);

	printf("Press any key to exit...\n");
	getchar();
	return EXIT_SUCCESS;
}
