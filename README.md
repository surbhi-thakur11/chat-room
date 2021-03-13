# chat-room in C
 
> Project Description

A simple chat client which allows 3 or more members to connect and chat
with each other in the room.  
Names of the particpants to be taken when they join the chat.  
Names of the participants to be displayed while chatting.  
Message sent by one participant should be broadcasted to all the 
participants in the chat room.  


Group members (Collaborators):  
PathiSamanvithaReddy  
surbhi-thakur11  
Ishpreet21698  

To run the code, please use Linux OS or VMware(in Windows OS):  

Open 1 Terminal for Server and type->  
>gcc server.c -pthread  
>./a.out  

For every other Terminal opened for each client, type->  
>cc client.c -pthread -o client
>./client