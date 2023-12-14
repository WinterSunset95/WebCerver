/*
Reading materials
https://stackoverflow.com/questions/176409/build-a-simple-http-server-in-c
https://blog.abhi.host/blog/2010/04/15/very-simple-http-server-writen-in-c/
https://www.jmarshall.com/easy/http/
https://tinyhttpd.sourceforge.net/
https://www.rfc-editor.org/rfc/rfc9110
https://en.wikipedia.org/wiki/Berkeley_sockets
https://dev.to/sanjayrv/a-beginners-guide-to-socket-programming-in-c-5an5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void *handle_connection(void *sock_desc) {
	// Get the socket descriptor
	int clientSocket = *(int*)sock_desc;

	// Send connection confirmation to the client
	char message[] = "Ayyy, this is your server speaking";
	send(clientSocket, message, sizeof(message), 0);

	// After that we listen in a never ending loop and echo whatever the client sends
	while (1) {
		char buffer[1024];
		recv(clientSocket, buffer, sizeof(buffer), 0);
		printf("Client %d says: %s", clientSocket, buffer);
		send(clientSocket, buffer, sizeof(buffer), 0);
	}

	return 0;
}

int main(void) {
  // Socket creation
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // Peparing server address struct
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // Now we bind
  bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  // Then we listen
  listen(serverSocket, 5);

  printf("Server listening on port 12345 . . . . \n");

  // Accept incoming connections
  while (1) {
	  int clientSocket = accept(serverSocket, NULL, NULL);
	  pthread_t thread_id;
	  pthread_create(&thread_id, NULL, handle_connection, (void*)&clientSocket);
  }

  // Try to send a message
  // char message[] = "Hello from server";
  // send(clientSocket, message, strlen(message), 0);

  // Lets recieve messages from the client in a loop
  // while (1) {
  //   char message[1024];
  //   char buffer[1024];
  //   printf("Enter message for client: ");
  //   fgets(message, sizeof(message), stdin);
  //   send(clientSocket, message, sizeof(message), 0);
  //   recv(clientSocket, buffer, sizeof(buffer), 0);
  //   printf("Client says: %s\n", buffer);
  // }

  // The above code, but with multithreading

  // Now we close sockets
  close(serverSocket);
  // close(clientSocket);
  
  return 0;
}
