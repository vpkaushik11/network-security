#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    int connectionCount = 0;
    socklen_t addr_size;

    // Create the socket
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    // Configure the server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for incoming connections
    listen(serverSocket, 2);

    while (true) {
        addr_size = sizeof(serverStorage);

        if (connectionCount > 2) {
            std::cerr << "Error: Maximum connection queue limit reached." << std::endl;
        } else {
            newSocket = accept(serverSocket, (struct sockaddr*)&serverStorage, &addr_size);
            connectionCount++;

            // Receive the combined buffer
            struct {
                struct tcphdr tcp_header;
                char message[1024];  // Adjust the size as needed
            } packet;

            recv(newSocket, &packet, sizeof(packet), 0);

            std::cout << "Received: " << packet.message << std::endl;
        
            // Close the socket for this connection
            close(newSocket);
            connectionCount--;
        }
    }

    close(serverSocket);

    return 0;
}
