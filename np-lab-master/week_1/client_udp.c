#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define MAXSIZE 50

int main()
{
  int sockfd, retval;
  int recedbytes, sentbytes;
  struct sockaddr_in serveraddr, clientaddr;
  char buff[MAXSIZE];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1)
  {
    printf("\nSocket Creation Error");
    return 0;
  }
  printf("Socket created\n");
  
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(3388);
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int size = sizeof(serveraddr);
  
  clientaddr.sin_family = AF_INET;
  clientaddr.sin_port = htons(3389);
  clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  retval = bind(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
  if(retval == 1)
  {
    printf("Binding error");
    close(sockfd);
  }
  printf("Socket bound\n");

  char pal = 'n';
  int len, vowel[5];
  do {  
    printf("Enter the text\n");
    scanf("%s", buff);
    
    sentbytes = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(sentbytes == -1)  {
      printf("Sending error\n");
      close(sockfd);
    }
    
    recvfrom(sockfd, &pal, sizeof(pal), 0, (struct sockaddr *)&serveraddr, &size); //palindrome or not
    recvfrom(sockfd, &len, sizeof(len), 0, (struct sockaddr *)&serveraddr, &size); //length of string
    recvfrom(sockfd, &vowel, sizeof(vowel), 0, (struct sockaddr *)&serveraddr, &size); //no of vowels
    
    printf("Is it a palindrome: %c\n", pal);
    printf("Length of string: %d\n", len);
    printf("No of vowels: (a, e, i, o, u)\n");
    int i;
    for(i = 0; i < 5; i++)
      printf("%d ", vowel[i]);
    printf("\n");

  }while(strcmp(buff, "halt") != 0);
  
  close(sockfd);
}
