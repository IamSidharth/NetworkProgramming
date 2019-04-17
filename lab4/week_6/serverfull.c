#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>


int main()
{
  int s, r, x;
  
  printf("INPUT port number: ");
  scanf("%d", &x);
  
  char send_buffer[512];
  char recv_buffer[512];
  bzero(&send_buffer, sizeof(send_buffer));
  bzero(&recv_buffer, sizeof(recv_buffer));

  socklen_t len;
  struct sockaddr_in server, client;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
  {
    printf("\nSocket creation error.");
    exit(0);
  }

  printf("\nSocket created.");
  server.sin_family = AF_INET;
  server.sin_port = htons(x);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  
  r = bind(s, (struct sockaddr*)&server, sizeof(server));
  if(r == -1)
  {
    printf("\nBinding error.");
    exit(0);
  }

  printf("\nSocket binded.");
  
  r = listen(s, 5);
  if(r == -1)
  {
    close(s);
    exit(0);
  }

  printf("\nSocket listening.");

  pid_t pid;
  int newfd = accept(s, (struct sockaddr *)&client, &len);
 
  fflush(stdin);
  pid = fork();

  if(pid == 0) { //child
    while(1) {
      bzero(&recv_buffer, sizeof(recv_buffer));
      recv(newfd, recv_buffer, sizeof(recv_buffer), 0);
      if(strcmp(recv_buffer, "BYE\n") == 0)
        break;
      printf("Client: %s\n", recv_buffer);
    }
    
  }
  else {
    while(1) {
      bzero(&send_buffer, sizeof(send_buffer));
      printf("\nEnter message: ");
      fgets(send_buffer, sizeof(send_buffer), stdin);
      if(strcmp(send_buffer, "BYE\n") == 0)
        break;
      send(newfd, send_buffer, strlen(send_buffer) + 1, 0);
      printf("\nMessage sent.\n");
    }
    
  }

  close(newfd);
  close(s);
}
