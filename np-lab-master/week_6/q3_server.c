#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<ctype.h>
#include<sys/wait.h>
#include<fcntl.h> 
#include<ctype.h>

int main()
{
  int sockfd, newsockfd, portno;
  printf("Enter port no: ");
  scanf("%d", &portno);
  char buff[100];
  struct sockaddr_in serveraddr, client;

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(portno);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
  listen(sockfd, 5);
  
  socklen_t len = sizeof(client);
  newsockfd = accept(sockfd,(struct sockaddr *)&client,&len);
  
  recv(newsockfd, buff, sizeof(buff),0);

  int pid;
  char pid_line[50];
  
  FILE *fp = fopen("output.txt", "w");
  FILE *fp2 = fopen("output2.txt", "w");
  pid = fork();

  if(pid == 0) { //child
    FILE *filepointer = fopen(buff, "r");
      char line[1024];
      while(fgets(line, 1024, filepointer) != NULL) {
        int i = 0;
        int k = strlen(line);
        while(i < k) {
          line[i] = toupper(line[i]);
          i++;
        }
        fputs(line, fp);
        fputs("\n", fp);
        fflush(fp);
      }    
      sprintf(pid_line, "Process id: %d\n", getpid());
      fputs(pid_line, fp);
      fclose(filepointer);
      exit(0);
  }
  else { //parent
    wait(NULL);
    FILE *filepointer = fopen(buff,"r");
    char line[1024];
    while(fgets(line, 1024, filepointer) != NULL) {
      int i = 0;
      int k = strlen(line);
      while(i < k) {
        if(isalpha(line[i])) {
          int digit = toupper(line[i]) - 'A';
          char str[3];
          sprintf(str, "%d", digit);
          fputs(str, fp2);
        }
        else {
          fputc(line[i], fp2);
        }
        i++;
      }
      fflush(fp2);
    }
    sprintf(pid_line, "Process id: %d\n", getpid());
      fputs(pid_line, fp2);

    fclose(filepointer);
  }
  
  close(newsockfd);
  close(sockfd);

  fclose(fp);
  fclose(fp2);
}
