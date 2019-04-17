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

int main()
{
  int s, r, x;
  char ip[INET_ADDRSTRLEN];
  printf("INPUT port number: ");
  scanf("%d", &x);
  printf("Enter server ip address: ");
  scanf("%s", ip);

  char send_buffer[512];
  char recv_buffer[512];
  bzero(&send_buffer, sizeof(send_buffer));
  bzero(&recv_buffer, sizeof(recv_buffer));


  struct sockaddr_in server;
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
  {
    printf("\nSocket creation error.");
    exit(-1);
  }
  
  printf("\nSocket created.");
  
  server.sin_family = AF_INET;
  server.sin_port = htons(x);
  server.sin_addr.s_addr = inet_addr(ip);
  
  r = connect(s, (struct sockaddr *)&server, sizeof(server));

  if(r == -1)
  {
    printf("\nConnection error.");
    exit(-1);
  }

  printf("\nSocket connected.");
  printf("\n\n");

  fflush(stdin);
  pid_t pid;
  pid = fork();

  if(pid == 0) { //child
    while(1) {
      bzero(&send_buffer, sizeof(send_buffer));
      printf("Enter message: ");
      fgets(send_buffer,sizeof(send_buffer), stdin);
      if(strcmp(send_buffer, "BYE\n") == 0) 
        break;
      send(s, send_buffer,strlen(send_buffer) + 1, 0);
      printf("\nMessage sent\n");
    }
  }
  else {
    while(1) {
      bzero(&recv_buffer, sizeof(recv_buffer));
      recv(s, recv_buffer, sizeof(recv_buffer), 0);
      printf("Server: %s\n", recv_buffer);
      if(strcmp(recv_buffer, "BYE\n") == 0)
        break;
    }
  }

  close(r);
  close(s);

  return 0;
}
