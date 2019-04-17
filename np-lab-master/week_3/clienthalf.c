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
  int s, x;
  printf("INPUT port number: ");
  scanf("%d", &x);

  char send_buffer[512];
  bzero(&send_buffer, sizeof(send_buffer));

  struct sockaddr_in server, client;
  socklen_t len = sizeof(server);
  s = socket(AF_INET, SOCK_DGRAM, 0);
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
  bind(s, (struct sockaddr *)&client, sizeof(client));


  while (1) {
    printf("\nEnter message: ");
    scanf("%s", send_buffer);
    sendto(s, send_buffer, sizeof(send_buffer), 0, (struct sockaddr *)&server, len);
    printf("Message sent\n");
    } 
  close(s);
  return 0;
}
