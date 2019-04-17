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
  int s, r, recb, sntb, x;
  printf("INPUT port number: ");
  scanf("%d", &x);
  struct sockaddr_in server;
  char buff[50];
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
  
  r = connect(s, (struct sockaddr *)&server, sizeof(server));

  if(r == -1)
  {
    printf("\nConnection error.");
    exit(-1);
  }

  printf("\nSocket connected.");
  printf("\n\n");

  int num_array[5];
  printf("Enter numbers: ");
  int i;
  for(i = 0; i < 5; i++)
    scanf("%d", &num_array[i]);
  
  int opt = 5;
 
  sntb = send(s, &num_array, sizeof(int) * 5, 0);
  if(sntb == -1) {
    printf("Integer array not sent\n");
    exit(-1);
  }

  while(1) {
    printf("Choose option:\n1.Search\n 2.Sort ascending\n3.Descending\n4.Split\n5.Exit\n");
    scanf("%d", &opt);

    send(s, &opt, sizeof(opt), 0);

    if(opt == 1) {
      printf("Enter search value: ");
      int search_val, pos;
      scanf("%d", &search_val);
      send(s, &search_val, sizeof(opt), 0);
      recv(s, &pos, sizeof(pos), 0);
      printf("Position: %d\n", pos);
    }
    else if(opt == 2 || opt == 3 || opt == 4) {
      recv(s, &num_array, sizeof(num_array), 0);
      printf("New array: \n");
      int i;
      for(i = 0; i < 5; i++)
        printf("%d ", num_array[i]);
      printf("\n");
    }

    if(opt == 5)
      break;
  }
  close(s);

  return 0;
}
