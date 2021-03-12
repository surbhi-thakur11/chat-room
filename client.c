#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


char msg[500];
char name[32];

void str_overwrite_stdout() {
  printf("%s", "> ");
  fflush(stdout);
}

void *recvmg(void *my_sock)
{
	int sock = *((int *)my_sock);
	int len;
	// client thread always ready to receive message
	while((len = recv(sock,msg,500,0)) > 0) {
		msg[len] = '\0';
		fputs(msg,stdout);
	}
}

int main(int argc,char *argv[]){
	pthread_t recvt;
	int len;
	int sock;
	char send_msg[500];
	struct sockaddr_in ServerIp;
	char client_name[100];

	printf("Please enter your name: ");
	fgets(name, 32, stdin);

	strcpy(client_name, name);
	sock = socket( AF_INET, SOCK_STREAM,0);
	ServerIp.sin_port = htons(8888);
	ServerIp.sin_family= AF_INET;
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	if( (connect( sock ,(struct sockaddr *)&ServerIp,sizeof(ServerIp))) == -1 )
		printf("\n connection to socket failed \n");
	
	//creating a client thread which is always waiting for a message
	pthread_create(&recvt,NULL,(void *)recvmg,&sock);

	printf("=== WELCOME TO THE CHATROOM ===\n");
	
	//ready to read a message from console
	while(fgets(msg,500,stdin) > 0) {
		str_overwrite_stdout();
		strcpy(send_msg,client_name);
		strcat(send_msg,":");
		strcat(send_msg,msg);
		len = write(sock,send_msg,strlen(send_msg));
		if (strcmp(msg, "exit") == 0){
			printf("\nBye\n");
			break;
		}
		if(len < 0) 
			printf("\n message not sent \n");
			
	}

	//while (1){
	//	if(flag){
	//		printf("\nBye\n");
	//		break;
    //}
	//}
	
	//thread is closed
	pthread_join(recvt,NULL);
	close(sock);
	return 0;
}
