#include <arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

void main()
{
int sockfd,retval;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr;
char buff[MAXSIZE];

sockfd=socket(AF_INET,SOCK_STREAM,0);

serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

// int nread = 8;
// write(sockfd, &nread, sizeof(int));
printf("enter the text\n");
scanf("%s",buff);
sentbytes=send(sockfd,buff,sizeof(buff),0);


recedbytes=recv(sockfd,buff,sizeof(buff),0);
puts(buff);
printf("\n");
close(sockfd);
}
