#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

pthread_mutex_t mutex;
int clients[20];
int n=0;
int l = sizeof(clients)/sizeof(clients[0]);  //find number of connected clients
void sendtoall(char *msg,int curr){
	int i;
	pthread_mutex_lock(&mutex);
	 
	for(i = 0; i < n; i++) {
		if(clients[i] != curr) {    //sending message to all clients expect the sender
			if(send(clients[i],msg,strlen(msg),0) < 0) {
				printf("sending failure n");
				continue;
			}
		}
	}
	pthread_mutex_unlock(&mutex);
}

void *recvmg(void *client_sock){
	int sock = *((int *)client_sock);
	char msg[500];
	int len;
	while((len = recv(sock,msg,500,0)) > 0) {
		msg[len] = '\0';     //initialize msg[len]
		sendtoall(msg,sock);  
	}
	
}

int main(){
	struct sockaddr_in ServerIp;
	pthread_t recvt;
	int sock=0 , Client_sock=0;
	
	ServerIp.sin_family = AF_INET;
	ServerIp.sin_port = htons(8888);
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock = socket( AF_INET , SOCK_STREAM, 0 );
	if( bind( sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp)) == -1 )
		printf("cannot bind, error!! \n");
	else
		printf("Server Started\n");  //binding to the server
		
	if( listen( sock ,50 ) == -1 )
		printf("listening failed \n");
		
	while(1){
	  
		if( (Client_sock = accept(sock, (struct sockaddr *)NULL,NULL)) < 0 )
		
			printf("accept failed  \n");
		pthread_mutex_lock(&mutex);
		clients[n]= Client_sock;
		n++;
		
		pthread_create(&recvt,NULL,(void *)recvmg,&Client_sock);   // creating a thread for each client 


		//here below, we had tried logic to accept minimum 3 clients; but wasn't working. So commented this part
		/*printf("%d",l);
		if (l<3){
		printf("Please add atleast 3 participants to start the chat");
		pthread_mutex_unlock(&mutex);
		//break;  //either break or continue shall come here
	}*/
	
		pthread_mutex_unlock(&mutex);
	}
	return 0; 
	
}
