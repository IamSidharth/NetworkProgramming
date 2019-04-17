#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <ctype.h>

#define MAXSIZE 90

char palindrome(char *string);
void count_vowels(char *string, int vowel[]);

int main()
{
  int sockfd, retval;
  socklen_t actuallen;
  int recedbytes, sentbytes;
  struct sockaddr_in serveraddr, clientaddr;

  char buff[MAXSIZE];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if(sockfd == -1)
  {
    printf("\nSocket creation error");
  }
  
  clientaddr.sin_family = AF_INET;
  clientaddr.sin_port = htons(3389);
  clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(3388);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if(retval == 1)
  {
    printf("Binding error\n");
    close(sockfd);
  }
  printf("Socket bound\n");

  char pal = 'n';
  int len, vowel[5];

  do {   
    recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&clientaddr, &actuallen);
    pal = palindrome(buff);
    len = strlen(buff);
    memset(&vowel, 0, sizeof(vowel));
    count_vowels(buff, &vowel);
    
    sendto(sockfd, &pal, sizeof(pal), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    sendto(sockfd, &len, sizeof(len), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    sendto(sockfd, &vowel, sizeof(vowel), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    
  }while(strcmp(buff, "halt") != 0);

  close(sockfd);
}

char palindrome(char *string) {
  int i = 0, len = strlen(string);
  while(string[i] != '\0') {
    if(string[i] != string[len - i - 1])
      return 'n';
    i++;
  }
  return 'y';
}

void count_vowels(char *string, int vowel[]) {
  int i = 0;
  while(string[i] != '\0') {
    switch(tolower(string[i])) {
      case 'a':
        vowel[0]++; break;
     case 'e':
        vowel[1]++; break;
     case 'i':
        vowel[2]++; break;
     case 'o':
        vowel[3]++; break;
     case 'u':
        vowel[4]++; break;
     default:
        break;
    }
    i++;
  }
}
