#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

char msg[500];
char name[20];
char *c_1 = "Samanvitha";
char *c_2 = "Surbhi";
char *c_3 = "Ishpreet";
char *c_4 = "Kushal";
//char *c_5 = "exit";
void *recvmg(void *my_sock)
{
	int sock = *((int *)my_sock);
	int len;
	
	while((len = recv(sock,msg,500,0)) > 0) {      // client thread always ready to receive message
		msg[len] = '\0';     //initialize msg[len]
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
	printf("Please enter your name :");  //getting participant name
	fgets(name,32,stdin); 	
	name[ strcspn( name, "\n" ) ] = '\0';
	
	for (int i = 0, k = strlen(name); i < k; i++)
{
    if (!isalpha(name[i]))   //if name contains any number, then re-enter name
    {
        printf("Error, Please enter valid name : ");
        fgets(name,32,stdin); 	
	name[ strcspn( name, "\n" ) ] = '\0';
        break;
    }
    
    
}
	if (strlen(name) > 20 || strlen(name) < 3){   //if length of name doesn't satisfy this condition, then re-enter name
		printf("Name must be less than 20 and more than 2 characters.\n");
		printf("Please enter your name again:");
		fgets(name,32,stdin); 	
	name[ strcspn( name, "\n" ) ] = '\0';
        //break;
	}
	
	if (strcmp(name,c_1)!=0 && strcmp(name,c_2)!=0 && strcmp(name,c_3)!=0 && strcmp(name,c_4)!=0)  //trying to only accept the client name which is hardcoded here
	{  //couldn't implement functionality of admin approving client into the chat, so tried this instead
		printf("Client name not matching! Please enter valid client: \n");
			fgets(name, 32, stdin);
			name[ strcspn( name, "\n" ) ] = '\0';
			
	}
	
	strcpy(client_name,name);
	sock = socket( AF_INET, SOCK_STREAM,0);
	ServerIp.sin_port = htons(8888);
	ServerIp.sin_family= AF_INET;
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	if( (connect( sock ,(struct sockaddr *)&ServerIp,sizeof(ServerIp))) == -1 )  //socket connection
		printf("\n connection to socket failed \n");
	
	
	pthread_create(&recvt,NULL,(void *)recvmg,&sock);    //creating a client thread which is always waiting for a message
	printf("==========Welcome to the chat room==========\n");  //entering the chat
	printf("===========Press Ctrl+Z to end the chat=========\n"); //type ctrl+z to exit the chat
	
	while(1){
	
	if (fgets(msg,500,stdin) > 0)   //ready to read a message from console
	
	 {
		strcpy(send_msg,client_name);  //format of text as seen in the chat terminal
		strcat(send_msg,":");          //format of text as seen in the chat terminal
		strcat(send_msg,msg);          //format of text as seen in the chat terminal
		len = write(sock,send_msg,strlen(send_msg));
		if(len < 0) {
			printf("\n message not sent \n");
			}


		//here below, we had tried logic to exit the socket if the participant types 'exit' and the chat should close; but wasn't working. So commented this part
		/*if (strcmp(msg,c_5)==0)
		  {
		    printf("\nConnection ended.Please reconnect\n");
		    pthread_join(recvt,NULL);
	           close(sock);
		    }*/
			
	}
	}
	
	
	pthread_join(recvt,NULL);   //thread is closed
	close(sock);
	return 0;
}
