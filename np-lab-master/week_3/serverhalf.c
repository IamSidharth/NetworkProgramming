#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>


void swap(char *a, char *b) {
  char t = *a;
  *a = *b;
  *b = t; 
}

void permute(char *a, int i, int n) {
   int j; 
   if (i == (n - 1))
     printf("%s\n", a);
   else {
     for (j = i; j < n; j++) {
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); 
       }
   }
} 

int main()
{
  int s, r, x;
  
  printf("INPUT port number: ");
  scanf("%d", &x);
  
  char recv_buffer[512];
  bzero(&recv_buffer, sizeof(recv_buffer));

  struct sockaddr_in server, client;
  socklen_t len = sizeof(client);
  
  s = socket(AF_INET, SOCK_DGRAM, 0);
  if(s == -1)
  {
    printf("\nSocket creation error.");
    exit(0);
  }

  printf("\nSocket created.");
  server.sin_family = AF_INET;
  server.sin_port = htons(x);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  /*
  client.sin_family = AF_INET;
  client.sin_port = htons(x) + 1;
  client.sin_addr.s_addr = htonl(INADDR_ANY);
  */

  r = bind(s, (struct sockaddr*)&server, sizeof(server));
  if(r == -1)
  {
    printf("\nBinding error.");
    exit(0);
  }

  printf("\nSocket binded.");
  
  while(1) {
    recvfrom(s, &recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *)&client, &len);
    permute(recv_buffer, 0, strlen(recv_buffer));
}
  close(s);
}
