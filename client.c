#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main() {
    // First we create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Then we prepare the server address struct
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "localhost", &serverAddr.sin_addr);

    // Now we connect to the server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // And we recieve the data
    while (1) {
        char message[1024];
        printf("Enter your message: ");
        fgets(message, sizeof(message), stdin);
        send(clientSocket, message, sizeof(message), 0);
    }

    // Close the client
    close(clientSocket);

    return 0;
    
}
