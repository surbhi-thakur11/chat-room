//To run the code enter "./a.out Name" 
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


char msg[500];


int main(int argc,char *argv[])
{
	//Declaring variables
	int len;
	int sock;
	int c;
	char send_msg[500];
	struct sockaddr_in server_ip;
	char client_name[100];
	
	//storing name entered by client in variable 'client_name'
	strcpy(client_name, argv[1]); //argv[1] takes the name that client enters 
	
	//Creating TCP socket
	sock = socket( AF_INET, SOCK_STREAM,0);
	if (sock !=-1)
	{
	 printf("Socket Created\n");
	 }
	else 
	 printf("Couldn't create socket\n");
	 
	//Socket Settings
	server_ip.sin_port = htons(8888);
	server_ip.sin_family= AF_INET;
	server_ip.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//Connecting socket to Server's address
	c=connect( sock ,(struct sockaddr *)&server_ip,sizeof(server_ip));
	if( c != -1 )
		printf("Connected to server \n");
	else
		printf("Connection failed \n");
		
	close(sock);
	return 0;
}
