#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>

int main()
{
  int s, r, x, ns;
  printf("INPUT port number: ");
  scanf("%d", &x);
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
  
  r = listen(s, 1);
  if(r == -1)
  {
    close(s);
    exit(0);
  }

  printf("\nSocket listening.\n");
  len = sizeof(client);
  pid_t pid;
  int client_count = 0, sockfds[5];

  char buff[512];
  memset(buff, 0, sizeof(buff));

  while(1) {
    ns = accept(s, (struct sockaddr*)&client, &len);
    sockfds[client_count++] = ns;

    // close connections with all clients
    if(client_count > 2) {
      printf("Terminate sessions\n");
      int i;
      for(i = 0; i < client_count; i++) {
        //send to each client
        close(sockfds[i]);
      }

      close(s);
      exit(0);
    }

    // child process
    if((pid = fork()) == 0) {
      close(s);
      printf("Connected to client %d\n", client_count);
      char ip[INET_ADDRSTRLEN];
      inet_ntop (AF_INET, &(client.sin_addr), ip, sizeof (ip));
      int port = ntohs(client.sin_port);
      printf("Socket address: %s %d\n", ip, port);

      recv(ns, buff, sizeof(buff), 0);      
      printf("Received: %s\n", buff);

      if(client_count == 2) {
        FILE *in = fopen("dummy", "r");
        char file_buff[512];
        fscanf(in, "%s", file_buff);
        fclose(in);
        strcat(file_buff, " Institute of");
        strcat(file_buff, " Technology");

        printf("%s\n", file_buff);

      }
      close(ns);
      exit(0);
    }
    
    close(ns);
  }
}
