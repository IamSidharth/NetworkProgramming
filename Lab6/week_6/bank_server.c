#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#include "helpers.h"

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

  char uname[50], password[50], e_password[50];
  int user_login, opt, amount;

  recv(ns, uname, sizeof(uname), 0);
  recv(ns, password, sizeof(password), 0);

  strcpy(e_password, encrypt(password, 3));
  user_login = check_user(uname, e_password);
  send(ns, &user_login, sizeof(user_login), 0);

  if(user_login == -2) {
    printf("Incorrect username\n");
    exit(0);
  }
  else if(user_login == -1) {
    printf("Incorrect password\n");
    exit(0);
  }

  printf("User logged in\n");
  while(1) {
    recv(ns, &opt, sizeof(opt), 0);
    
    if(opt == 1) {
      recv(ns, &amount, sizeof(amount), 0);
      update_balance(uname, e_password, -amount);
    }
    else if(opt == 2) {
      recv(ns, &amount, sizeof(amount), 0);
      update_balance(uname, e_password, amount);
    }
    else if(opt == 3) {
      int balance = get_balance(uname, e_password);
      send(ns, &balance, sizeof(balance), 0);
    }
    else
      break;
  }
  close(ns);
  close(s);
}
