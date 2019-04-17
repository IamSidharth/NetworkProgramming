#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include <arpa/inet.h>


int anagram(char a[], char b[])
{
    int m = strlen(a);
    int n = strlen(b);
    
    char temp;
    
    if(m != n)
      return 0;
    
    int i, j;
      
    for(i = 0; i < n - 1; i++) {
      for(j = i + 1; j < n; j++) {
        if(a[i] > a[j]) {  
          temp = a[i];
          a[i] = a[j];
          a[j] = temp;
        }
        if(b[i] > b[j]) {  
          temp = b[i];
          b[i] = b[j];
          b[j] = temp;
        }
      }
    }
      
    for(i = 0; i < n; i++) { 
      if(a[i] != b[i]) { 
        return 0;
      }
    }
    return 1;     
}


int main()
{

  int sockfd, newsockfd, portno, f;
  socklen_t len;
  f = 1;
  printf("Enter port no: ");
  scanf("%d", &portno);
  char buff1[50];
  char buff2[50];
  char ans[50];
  struct sockaddr_in serveraddr, clientaddr;

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(portno);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  sockfd = socket(AF_INET,SOCK_STREAM, 0);
  bind(sockfd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
  listen(sockfd, 1);
  len = sizeof(clientaddr);


  while(1) {  
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);
    recv(newsockfd, buff1, sizeof(buff1), 0);
    send(newsockfd, &f, sizeof(f), 0);
    recv(newsockfd,buff2, sizeof(buff2), 0);
    send(newsockfd, &f, sizeof(f), 0);
    int d;
    d = anagram(buff1, buff2);
    memset(ans, 0, sizeof(ans));
    if(d == 0) { 
      strcat(ans,"Not Anagrams");
    }
    else {
      strcat(ans,"Anagrams");
    }
    time_t t = time(NULL);
    struct tm curr_time = *localtime(&t);
    printf("Current time: %d-%d-%d %d:%d:%d\n", curr_time.tm_year + 1900, curr_time.tm_mon + 1, curr_time.tm_mday, curr_time.tm_hour, curr_time.tm_min, curr_time.tm_sec);
    int port = ntohs(clientaddr.sin_port);
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientaddr.sin_addr), ip, sizeof(ip));
    printf("Socket address: %s %d\n", ip, port);

    send(newsockfd, ans,sizeof(ans), 0);
    recv(newsockfd, &f,sizeof(f), 0);
  }
  close(newsockfd);
  close(sockfd);

  return 0;
}
