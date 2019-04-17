#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h> 
#include<arpa/inet.h>




void main(){

int sockfd,g[1],errfd,portno,sendb,recvb,w[1],x[1],y[1],z[1];
char input[100];
char don[50];
portno = 8555;

struct sockaddr_in serveraddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);

serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(portno);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));


printf("Enter Filename:");
scanf("%s",input);

send(sockfd,input,sizeof(input),0);
recv(sockfd,g,sizeof(g),0);

recv(sockfd,don,sizeof(don),0);
send(sockfd,g,sizeof(g),0);

close(sockfd);
}
