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
  printf("INPUT port number: ");
  scanf("%d", &x);
  struct sockaddr_in server, client;

  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
  {
    printf("\nSocket creation error.");
    exit(-1);
  }
  
  printf("\nSocket created.");
  
  server.sin_family = AF_INET;
  server.sin_port = htons(x);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  client.sin_family = AF_INET;
  client.sin_port = htons(x) + 1;
  client.sin_addr.s_addr = inet_addr("127.0.0.1");

  
  r = connect(s, (struct sockaddr *)&server, sizeof(server));

  if(r == -1)
  {
    printf("\nConnection error.");
    exit(-1);
  }

  printf("\nSocket connected.");
  printf("\n\n");

  char str[50] = "Institute of";
  send(s, str, sizeof(str), 0);
  printf("Sent: %s\n", str);
  close(s);

  return 0;
}
