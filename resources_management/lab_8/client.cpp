#pragma comment (lib,"Ws2_32.lib")
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT_NUM 2088

int main()
{
	int sock;
	int err;
	struct sockaddr_in addr;
	char ip[30];
	char recvbuf[256];
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NUM);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	printf("Client is created\n");
	err = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	
	if (err == -1)
	{
		printf("Can't connect to server\n");
		return 1;
	}
	printf("List of users IP:\n");
	recv(sock, recvbuf, sizeof(recvbuf), 0);
	printf("%s\n", recvbuf);
	while (strcmp(recvbuf, "that's all") != 0)
	{
		recv(sock, recvbuf, sizeof(recvbuf), 0);
		printf("%s\n", recvbuf);
	}
	while (1)
	{
		recv(sock, recvbuf, sizeof(recvbuf), 0);
		printf("The new user's IP is: %s\n", recvbuf);
	}
}
