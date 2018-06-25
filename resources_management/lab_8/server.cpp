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

	// Bind socket.
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serv_sock, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) {
		perror("bind failed");
		return EXIT_FAILURE;
	}
	printf("Socket binded\n");

	// Listen socket.
	int queue_size = 1;
	printf("Listening socket...\n");
	if (listen(serv_sock, queue_size) < 0) {
		perror("listen failed");
		return EXIT_FAILURE;
	}
	
	// Accept connection.
	int client_sock = accept(serv_sock, NULL, NULL);
	if (client_sock < 0) {
		perror("accept failed");
		return EXIT_FAILURE;
	}
	printf("Connection accepted\n");

	char buf[128] = { '\0' };
	recv(client_sock, buf, sizeof(buf), 0);
	printf("Recived text: '%s'\n", buf);

	printf("Press any key to exit...\n");
	getchar();
	return EXIT_SUCCESS;
}
