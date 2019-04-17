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

int main() {

  int sockfd, errfd, portno, f;
  f = 1;
  printf("Enter port no: ");
  scanf("%d", &portno);
  char s1[50];
  char s2[50];
  char ans[50];
  struct sockaddr_in serveraddr;
  sockfd = socket(AF_INET,SOCK_STREAM,0);

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(portno);
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  errfd = connect(sockfd, (struct sockaddr*)&serveraddr,sizeof(serveraddr));
  
  if(errfd == -1) {
    exit(0);
  }
  printf("Enter string 1:\n");
  scanf("%s", s1);
  
  printf("Enter string 2:\n");
  scanf("%s", s2);
  
  send(sockfd, s1, sizeof(s1), 0);
  recv(sockfd, &f, sizeof(f), 0); 
  
  send(sockfd, s2, sizeof(s2), 0);
  recv(sockfd, &f, sizeof(f), 0);
  
  recv(sockfd, ans, sizeof(ans), 0);
  send(sockfd, &f, sizeof(f), 0);

  printf("%s\n", ans);
  close(sockfd);

  return 0;
}

