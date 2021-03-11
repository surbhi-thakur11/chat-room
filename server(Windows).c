  
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	char *message;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket  using create(), Create TCP socket.
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	//Prepare the sockaddr_in structure,assign IP, PORT 
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	// Bind the socket to server address.
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	puts("Bind done");

	//Listen to incoming connections using listen(), put the server socket in a passive mode, where it waits for the client to approach the server to make a connection
	listen(s , 3);
	
	//Accept and incoming connection At this point, connection is established between client and server, and they are ready to transfer data.
	puts("Waiting for incoming connections...");
	
	c = sizeof(struct sockaddr_in);
	
	while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
	{
		puts("Connection accepted");
		
		//Reply to the client
		message = "Hello Client , I have received your connection. But I have to go now, bye\n";
		send(new_socket , message , strlen(message) , 0);
	}
	
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
		return 1;
	}

	closesocket(s);
	WSACleanup();
	
	return 0;
}