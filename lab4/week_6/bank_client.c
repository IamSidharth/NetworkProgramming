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
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  r = connect(s, (struct sockaddr *)&server, sizeof(server));

  if(r == -1)
  {
    printf("\nConnection error.");
    exit(-1);
  }

  printf("\nSocket connected.");

  char uname[50], password[50];

  printf("Enter username, password:\n");
  scanf("%s", uname);
  scanf("%s", password);

  send(s, uname, sizeof(uname), 0);
  send(s, password, sizeof(password), 0);

  int user_login, opt, amount, balance;
  recv(s, &user_login, sizeof(user_login), 0);
  
  if(user_login != 1) {
    printf("Login not successful\n");
    exit(0);
  }

  while(1) {
    printf("1. Debit\n2. Credit\n3. View Balance\n4. Exit\n");
    scanf("%d", &opt);

    send(s, &opt, sizeof(opt), 0);

    if(opt == 1 || opt == 2) {
      printf("Enter amount to be updated: \n");
      scanf("%d", &amount);
      send(s, &amount, sizeof(amount), 0);

      printf("Balance updated\n");
    }
    else if(opt == 3) {
      recv(s, &balance, sizeof(balance), 0);
      printf("Balance: %d\n", balance);
    }
    else break;
  }
  close(s);

  return 0;
}
