#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT_NUM 2088
int Sockets[15];
struct sockaddr_in AllAddr[15]; 

int main()
{
	int ClientSock;
	int i;
	int err;
	int ListSock;
	int ConnectSock;
	struct sockaddr_in addr;
	int curr = 0;
	
	ListSock = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NUM);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	err = bind(ListSock, (struct sockaddr *) &addr, sizeof(addr));
	if (err == -1)
	{
		printf("Can't bind");
		return 1;
	}
	printf("Binded\n");
	err = listen(ListSock, 10);
	if (err == -1)
	{
		printf("Can't listen");
			return 1;
	}
	printf("Listening\n");
	while (1)
	{
		struct sockaddr_in from;
		int fromlen = sizeof(from);
		ClientSock = accept(ListSock, (struct sockaddr*)&from, &fromlen);
		if (ClientSock == -1)
		{
			printf("Can't accept\n");
			return 1;
		}
		printf("Somebody is accepted\n");
		printf("Sending data to clients\n");
		if (curr < 15)
		{
			AllAddr[curr] = from;
			Sockets[curr] = ClientSock;
			for (i = 0; i < curr; i++)
			{	
				send(Sockets[i], inet_ntoa(from.sin_addr), 256, 0);
				send(ClientSock, inet_ntoa(AllAddr[i].sin_addr), 256, 0);
			}
			send(ClientSock, "that's all", 256, 0);
			curr++;
		}
		else 
		{
			printf("Too much people on the lane");
			return 1;
		}
		printf("Data is sended\n");
		ClientSock = -1;
	}
}
