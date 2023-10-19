#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> 
#include <sys/socket.h>
#include <unistd.h> 
#define MAX 4
#define PORT 8080
#define SA struct sockaddr

// gcc client.c -fno-stack-protector -o client : to run the client program.

void loginFunc(int sockfd)
{
	char clientBuffer[MAX];
	int authToken;
	bzero(clientBuffer, sizeof(clientBuffer));
	printf("Client: Enter password\n");
	gets(clientBuffer);
	write(sockfd, clientBuffer, sizeof(clientBuffer));
	read(sockfd, &authToken, sizeof(authToken));
	printf("Server has sent - %d\n", ntohl(authToken));
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	loginFunc(sockfd);

	close(sockfd);
}