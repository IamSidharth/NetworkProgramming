#include <arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

void main()
{
FILE *fp;
 char line[130];
int sockfd,newsockfd,retval;
socklen_t actuallen;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr,clientaddr;
char buff[MAXSIZE];
char buff_return[MAXSIZE] = "";
char cmd[MAXSIZE] = "grep '";
int a=0;

sockfd=socket(AF_INET,SOCK_STREAM,0);

serveraddr.sin_family=AF_INET;

serveraddr.sin_port=htons(3388);//define port num
serveraddr.sin_addr.s_addr=htons(INADDR_ANY);//define IP Addrs
retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));


retval=listen(sockfd,1);


actuallen=sizeof(clientaddr);
newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);



// int value;
// read(sockfd, &value, sizeof(int));
// printf("%d\n",value);
recedbytes=recv(newsockfd,buff,sizeof(buff),0);
strcat(cmd , buff);
strcat(cmd , "'");
strcat(cmd , " database");

//Server Real Code HERE
fp = popen(cmd , "r");
while ( fgets( line, sizeof line, fp))
strcat(buff_return,line);


sentbytes=send(newsockfd,buff_return,sizeof(buff),0);

if(sentbytes==-1)
{
close(sockfd);
close(newsockfd);
}

close(sockfd);
close(newsockfd);
}