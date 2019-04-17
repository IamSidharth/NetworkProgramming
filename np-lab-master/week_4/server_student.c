#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#include "student.h"

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

  printf("\nSocket listening.");
  len = sizeof(client);
  ns = accept(s, (struct sockaddr*)&client, &len);
  if(ns == -1)
  {
    close(s);
    exit(0);
  }

  printf("\nSocket accepting.");

  int opt;
  while(recv(ns, &opt, sizeof(opt), 0) != -1) {
    struct student *s = (struct student *)malloc(sizeof(struct student));
    create_student(s);
    if(opt == 1) {
      long reg_no;
      recv(ns, &reg_no, sizeof(reg_no), 0);
      s = search_reg_no(reg_no);
      if(s != NULL)
        print_student(s);
      else printf("Not found\n");
    }
    else if(opt == 2) {
      char name[30];
      recv(ns, name, sizeof(name), 0);
      s = search_name(name);
      if(s != NULL)
        print_student(s);
      else printf("Not found\n");
    }
    else if(opt == 3) {
      char subject_code[10];
      recv(ns, subject_code, sizeof(subject_code), 0 );
      s = search_subject_code(subject_code);
      if(s != NULL)
        print_student(s);
      else printf("Not found\n");
    }
    else break;
  }
  printf("\n");
  
  close(ns);
  close(s);
}
