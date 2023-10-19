#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define MAX 4 
#define PORT 8080 
#define SA struct sockaddr 

// gcc server.c -fno-stack-protector -o server : to run the server.

char password[] = "abc123";
char passBuffer[80];

void authFunc(int connfd) 
{ 
    char enteredPassword[8];
    int authFlag = 0;
    int convertedAuthFlag;
    read(connfd, passBuffer, sizeof(passBuffer));
    printf("\nClient has sent: %s", passBuffer);
    strcpy(enteredPassword, passBuffer);
    if(strcmp(enteredPassword, password)==0)
    {
		printf("\nCredentials correct!\n");
        authFlag = 1;
    }
	else
	{
		printf("\nIncorrect credentials!\n");
	}
    
    if(authFlag != 0)
    {
        printf("\nServer - Access Granted!\n");
    }
    else
    {
        printf("\nServer - Access Denied! Wrong Password.\n");
    }
    convertedAuthFlag = htonl(authFlag);
    write(connfd, &convertedAuthFlag, sizeof(convertedAuthFlag));
    bzero(passBuffer, sizeof(passBuffer));
} 

int main() 
{ 
	int sockfd, connfd, len; 
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server accept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server accept the client...\n"); 

	authFunc(connfd); 

	close(sockfd); 
}