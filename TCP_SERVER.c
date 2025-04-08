#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h
int main(void){
    int sockid, client_sock, client_size;
    struct sockaddr_in server,client;
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
    if(bind(sockid,(struct sockaddr*)&server,sizeof(server))<0){
        printf("Couldn't bind");
        return -1;
    }
    printf("Binding done");
    if(listen(sockid,1)<0){
        printf("Couldn't listen");
        return -1;
    }
    printf("Listening...");
    client_size=sizeof(client);
    client_sock=accept(sockid,(struct sockaddr*)&client,sizeof(client));
    if(client_sock<0){
        printf("Couldn't accept");
        return -1;
    }
    if(recv(client_sock,c_message,sizeof(c_message),0)){
        printf("Couldn't receive");
        return -1;
    }
    print("\nClient message: %s\n",c_message);
    printf("Enter the message to be send: ");
    scanf("%s",&s_message);
    if(send(client_sock,s_message,strlen(s_message),0)<0){
        printf("Couldn't Send");
        return -1;
    }
    close(client_sock);
    close(sockid);
    return 0;
}


