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

  int opt = 5;
 
  while(1) {
    printf("Choose option:\n1.Reg no\n2.Name\n3.Subject code\n4.Exit\n");
    scanf("%d", &opt);

    send(s, &opt, sizeof(opt), 0);

    if(opt == 1) {
      printf("Enter reg no: ");
      long reg_no;
      scanf("%ld", &reg_no);
      send(s, &reg_no, sizeof(reg_no), 0);
      //recv(s, &pos, sizeof(pos), 0);
      //printf("Position: %d\n", pos);
    }
    else if(opt == 2 ) {
      printf("Enter name: ");
      char name[30];
      scanf("%s", name);
      send(s, name, sizeof(name), 0);
      //recv(s, &num_array, sizeof(num_array), 0);
      //printf("New array: \n");
    }
    else if(opt == 3) {
      printf("Enter subject code: ");
      char subject_code[10];
      scanf("%s", subject_code);
      send(s, subject_code, sizeof(subject_code), 0);
    }

    else if(opt == 4)
      break;
  }
  close(s);

  return 0;
}
