#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(void)
{
int socket_desc, client_sock, client_size;
struct sockaddr_in server_addr;
char server_message[2000], client_message[2000];
memset(server_message, '\0', sizeof(server_message));
memset(client_message, '\0', sizeof(client_message));
socket_desc = socket(AF_INET, SOCK_STREAM, 0);
if (socket_desc < 0)
{
printf("Err while creating socket\n");
return -1;
}
printf("Socket created successfully\n");
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(2000);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
{
4
printf("Unable to connect");
return -1;
}
printf("Connected with server\n");
printf("Enter message: ");
scanf("%s", client_message);
if (send(socket_desc, client_message, strlen(client_message), 0) < 0)
{
printf("Can't send\n");
return -1;
}
if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
{
printf("Error while fetching server message...\n");
return -1;
}
printf("Server's response: %s\n", server_message);
close(socket_desc);
return 0;
}
5
PROGRAM(UDP_SERVER.C)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char **argv)
{
char *ip = "127.0.0.1";
int port = 4455;
int sockid;
struct sockaddr_in server_addr, client_addr;
char buffer[1024];
socklen_t addr_size;
int n;
sockid = socket(AF_INET, SOCK_DGRAM, 0);
if (sockid < 0) {
perror("[-]Socket error");
exit(1);
}
memset(&server_addr, '\0', sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = inet_addr(ip);
6
n = bind(sockid, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (n < 0) {
perror("[-] bind error");
exit(1);
}
bzero(buffer, 1024);
addr_size = sizeof(client_addr);
recvfrom(sockid, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);
printf("[+] Data recv: %s\n", buffer);
bzero(buffer, 1024);
strcpy(buffer, "welcome to the udp server");
sendto(sockid, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
printf("[+] Data send: %s \n", buffer);
return 0;
}
7
PROGRAM(UDP_CLIENT.C)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char **argv)
{
char *ip = "127.0.0.1";
int port = 4455;
int sockid;
int n;
struct sockaddr_in addr;
char buffer[1024];
socklen_t addr_size;
sockid = socket(AF_INET, SOCK_DGRAM, 0);
memset(&addr, '\0', sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_port = htons(port);
addr.sin_addr.s_addr = inet_addr(ip);
bzero(buffer, 1024);
strcpy(buffer, "Hello world!!");
sendto(sockid, buffer, 1040, 0, (struct sockaddr *)&addr, sizeof(addr));
printf("[+] Data send: %s\n", buffer);
8
bzero(buffer, 1024);
addr_size = sizeof(addr);
recvfrom(sockid, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
printf("[+] Data recv: %s \n", buffer);
return 0;
