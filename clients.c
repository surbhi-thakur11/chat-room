// to compile this file use "gcc clients.c -lws2_32" since we link ws2_32 library for winsock
// to run this file "filename <server ip addr> <port> <name>.exe" 
//To get port numbers that are free and different tcp connections on your pc use "netstat -a"
//Generally, port 8884 works on my pc

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h>   
#include <signal.h>
#include <sys/types.h> //used to define date datatypes, strutc dataypes
#include <winsock2.h> //functions related to socket
#include <windows.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define NAME_SIZE 25
#define buffer_size 100


/*
// error checking function
void Error(const char *errmessage)
{
	perror(errmessage); //inbuilt function to identify the error and give error description
	exit(1);  // to  terminate the program when error is found
}
*/
// Global Variables
char name[NAME_SIZE]="[Default]";


int main(int argc,char *argv[])
{	
	//Declarations
	WSADATA wsa;
	SOCKET SocketDesc;
	struct sockaddr_in server;  /* here, server is a variable of type sockaddr_in , sockaddr_in is structure that deals with IP addresses 
	                                and it has various methods like sin_family,sin_addr */
	char *message;
	
	/* if cl arguments donot contain required no. of arguments(i.e., 4 here),it shows required format to use and then exits */

	if (argc !=4)     //argc is of int type and used to store no. of arguments in command line arguments  
	{
		printf("Usage : %s <IP> <port> <name>\n",argv[0]);  
		exit(1);
	}
	

	// iniatilising winsock
	printf("Initialising Winsock\n");
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
	{
		printf("Failed.Error Code : %d",WSAGetLastError());
		return 1;
	}
	printf("Winsock Initialised\n");
	

	//Creating TCP Socket
	SocketDesc=socket(AF_INET,SOCK_STREAM,0);  // sock_stream used for TCP connection
	if(SocketDesc==INVALID_SOCKET)
	{
		printf("Socket can't be created:%d",WSAGetLastError());
	}
	else
	{
		printf("Socket created\n");
	}

    
    //Socket settings
   
	server.sin_addr.s_addr=inet_addr(argv[1]); /*inet_addr is a function to convert IP address(here, google.com's ip address) into long format
                                                         SocketDesc_addr contains IP address in long format */
	server.sin_family=AF_INET; 
 	server.sin_port=htons(atoi(argv[2])); // server's port no. that is mentioned in command line. argv[2] gives 3rd argument while executing client file i.e., port no

 	

 	//Connecting to Server
 	int con=connect(SocketDesc,(struct sockaddr *)&server,sizeof(server));
 	//printf("%d",con);
 	if(con==SOCKET_ERROR) // if connect() = -1 then no connection
 	{
 		puts("Connect() error");        // use cmd "netstat -a" to get ip address, ports and their status(listening/established)
 	}
 	else
 	{
 		puts("Connected to server");
 	}
 	

 	SendThread=(HANDLE)_beginthreadex(NULL,0,send_msg,(void*)&SocketDesc,0,NULL);
 	ReceiveThread=(HANDLE)_beginthreadex(NULL,0,receive_msg,(void*)&SocketDesc,0,NULL);

 	



    	return 0;
}

//Function to send message 

void send_msg(void *arg)  //send thread
{
	SOCKET SocketDesc=*((SOCKET*)arg);
	char NameMsg[NAME_SIZE+buffer_size];

	send(SocketDesc,name,strlen(name),0);  //sending name to server
	

	while(True)
	{
		fgets(message,buffer_size,stdin);
		// breaking the connection if a client says exit(i.e., q\n)
		if (strcmp(message,"q\n")||strcmp(message,"Q\n"))
		{
			closesocket(SocketDesc);
			exit(0);
		}
		sprintf(NameMsg,"%s %s",name,message);
		send(SocketDesc,NameMsg,strlen(NameMsg),0);
	}
	return 0;
}
