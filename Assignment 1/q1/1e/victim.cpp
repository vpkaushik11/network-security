#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // Create the socket
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    // Configure the server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Create a buffer to hold the TCP header and message
    struct {
        struct tcphdr tcp_header;
        char message[1024];  // Adjust the size as needed
    } packet;

    // Fill in the TCP header fields
    memset(&packet.tcp_header, 0, sizeof(packet.tcp_header));
    packet.tcp_header.source = htons(12345);  // Source port
    packet.tcp_header.dest = htons(12345);    // Destination port
    packet.tcp_header.syn = 1;               // SYN flag (set to 1)

    // Fill in the message
    const char* message = "Hello, Server! - From Client";
    strcpy(packet.message, message);

    // Send the combined buffer
    send(clientSocket, &packet, sizeof(packet), 0);

    // Close the socket
    close(clientSocket);

    return 0;
}
