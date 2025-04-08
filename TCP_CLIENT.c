#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(void){
    int sockid, client_sock, client_size;
    struct sockaddr_in server;
    char s_message[2000],c_message[2000];

    memset(s_message,'\0',sizeof(s_message));
    memset(c_message,'\0',sizeof(c_message));

    sockid=socket(AF_INET,SOCK_STREAM,0);
    if(sockid<0){
        printf("Couldn't create socket");
        return -1;
    }
    printf("socket created");

    server.sin_family=AF_INET;
    server.sin_port=htons(2000);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(sockid,(struct sockaddr*)&server,sizeof(server))<0){
        print("Couldn't connect");
        return -1;
    }
    print("Succesfully connected");
    print("Enter the message to be send:\n");
    scanf("%s",&c_message);
    if(send(server,c_message,strlen(c_message),0)<0){
        print("Couldn't send");
        return -1;
    }
    if(recv(server,s_message,sizeof(s_message),0)<0){
        print("Couldn't receive");
        return -1;
    }
    printf("Message received: %s",s_message);
    close(sockid);
    return 0;
}

