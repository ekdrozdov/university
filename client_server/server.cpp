#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	/*
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sin;
	socklen_t addressLength = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(8888);

	bind(tcp_socket, (struct sockaddr *) &sin, sizeof(sin));
	*/

	int newServerfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in localAddress;
	localAddress.sin_family = AF_INET;
	localAddress.sin_addr.s_addr = INADDR_ANY;
	localAddress.sin_port = htons(8888);
	socklen_t addressLength = sizeof(localAddress);
	getsockname(newServerfd, (struct sockaddr*)&localAddress,   \
			&addressLength);
	bind(newServerfd, (struct sockaddr *) &localAddress, 
			sizeof(localAddress));
	printf("local address: %s\n", inet_ntoa( localAddress.sin_addr));
	printf("local port: %d\n", (int) ntohs(localAddress.sin_port));

	return 0;
}
