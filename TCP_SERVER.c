#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(void) {
int socket_desc,client_sock,client_size;
struct sockaddr_in server_addr,client_addr;
char server_message[2000],client_message[2000];
memset(server_message,'\0',sizeof(server_message));
memset(client_message,'\0',sizeof(client_message));
socket_desc = socket(AF_INET,SOCK_STREAM,0);
if (socket_desc < 0) {
printf("Err while creating socket\n");
return -1;
}
printf("Socket created successfully\n");
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(2000);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
if (bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0) {
printf("Couldn't blind to the port\n");
return -1;
}
printf("\nDone with binding");
printf("\nListening for incoming connections...");
2
if (listen(socket_desc,1) < 0) {
printf("Error while listening\n");
return -1;
}
printf("Listening for incoming connections...");
client_size = sizeof(client_addr);
client_sock = accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
if (client_sock < 0) {
printf("Can't accept!!!");
return -1;
}
printf("Client connected to ip: %s & port : %i\n",inet_ntoa(client_addr.sin_addr),htons(client_addr.sin_port));
if (recv(client_sock,client_message,sizeof(client_message),0)
< 0) {
printf("Couldn't recieve");
return -1;
}
printf("\nMessage from client: %s\n",client_message);
printf("Enter server message: ");
scanf("%s",server_message);
if (send(client_sock,server_message,strlen(server_message),0) <0) {
printf("Can't send\n");
return -1;
}
close(client_sock);
close(socket_desc);
return 0; }
}
