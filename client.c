#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

void *sendThread(void *sock_desc) {
	int clientSocket = *(int*)sock_desc;
	while (1) {
		char message[1024];
		printf("-> ");
		fgets(message, sizeof(message), stdin);
		send(clientSocket, message, sizeof(message), 0);
	}
	close(clientSocket);
}

void *recvThread(void *sock_desc) {
	int clientSocket = *(int*)sock_desc;
	while (1) {
		char buffer[1024];
		recv(clientSocket, buffer, sizeof(buffer), 0);
		printf("-> %s ", buffer);
	}
	close(clientSocket);
}

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

	pthread_t thread_id;
	pthread_create(&thread_id, NULL, recvThread, (void*)&clientSocket);

	pthread_t thread_id2;
	pthread_create(&thread_id2, NULL, sendThread, (void*)&clientSocket);

	pthread_join(thread_id2, NULL);
	pthread_join(thread_id, NULL);

    // And we recieve the data
    // while (1) {
    //     char message[1024];
    //     printf("Enter your message: ");
    //     fgets(message, sizeof(message), stdin);
    //     send(clientSocket, message, sizeof(message), 0);
    // }

    // Close the client
    // close(clientSocket);

    return 0;
    
}
