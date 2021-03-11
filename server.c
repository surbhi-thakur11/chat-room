#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>


int main()
{       //Declaring variables 
	struct sockaddr_in server_ip , client;
	int sock=0 , client_sock=0;
	int n=0;
	int clients[20];
	
	//creating TCP socket
	sock = socket( AF_INET , SOCK_STREAM, 0 ); 
	if (sock !=-1)
	{
	 printf("Socket Created\n");
	 }
	else 
	 printf("Couldn't create socket\n");
	 
	//Socket Settings	
	server_ip.sin_family = AF_INET;
	server_ip.sin_port = htons(8888);  //port number
	server_ip.sin_addr.s_addr = inet_addr("127.0.0.1");  // assigning machine's ip address
	
	//Binding Socket to Server's address
	if( bind( sock, (struct sockaddr *)&server_ip, sizeof(server_ip)) != -1 )
		printf("Server Started\n");
	else
		printf("Error!! Cannot bind \n");

	
	//Listening to incoming connections from client.	
	if( listen( sock ,50 ) != -1 )
		printf("Listening to Clients... \n");
	else
		printf("listening failed \n");
	
	//Accepting client connections
	client_sock = accept(sock, (struct sockaddr *)&client,NULL);	
	while(1)
	{
		if((client_sock ) != -1 )
			printf("Connection not accepted\n");
		
		
			
			}
	
	return 0; 
	
}
