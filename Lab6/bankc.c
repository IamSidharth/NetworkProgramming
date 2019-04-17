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
#include<string.h>

void main(){

int sockfd,g[1],errfd,portno,sendb,recvb,f[1];
f[0]=1;
int c[2];
char username[50];
char password[50];
char ans[50];
char recvans[50];

portno = 8555;
struct sockaddr_in serveraddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(portno);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));


while(1)
{
  printf("Enter Username \n");
  gets(username);
  
  printf("Enter The Password \n");
  gets(password);
  
  send(sockfd,username,sizeof(username),0);
  recv(sockfd,g,sizeof(g),0);
  
  send(sockfd,password,sizeof(password),0);
  recv(sockfd,g,sizeof(g),0);
  
  recv(sockfd,ans,sizeof(ans),0);
  send(sockfd,f,sizeof(f),0);
  puts(ans);
  
  if(strcmp(ans,"1)Debit 2)Credit 3)Balance 4)Exit")!=0)
     {
       break;
     }
  printf("Enter Choice \n");
  scanf("%d",&c[0]);
  
  if(c[0]==1 || c[0]==2)
    {
       printf("Enter Amount \n");
       scanf("%d",&c[1]);
     }
  else{
     c[1]=0;
   }
   send(sockfd,c,sizeof(c),0);
  recv(sockfd,g,sizeof(g),0);
  
  recv(sockfd,recvans,sizeof(recvans),0);
  send(sockfd,f,sizeof(f),0);
  puts(recvans);

}

close(sockfd);
}
