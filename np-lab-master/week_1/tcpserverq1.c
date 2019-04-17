#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int search_array(int val, int array[]);
void sort_array(int array[], int opt);
void split_array(int array[]);

int main()
{
  int s, r, recb, sntb, x, ns, a = 0;
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
  
  int buff[5];

  recb = recv(ns, &buff, sizeof(buff), 0);
  if(recb == -1)
  {
    printf("\nMessage Receiving Failed");
    close(s);
    close(ns);
    exit(0);
  }

  int opt;
  while(recv(ns, &opt, sizeof(opt), 0) != -1) {
    if(opt == 1) {
      int search_val;
      recv(ns, &search_val, sizeof(search_val), 0);
      int pos = search_array(search_val, &buff);
      send(ns, &pos, sizeof(pos), 0);
    }
    else if(opt == 2) {
      sort_array(&buff, 1);
      send(ns, &buff, sizeof(buff), 0);
    }
    else if(opt == 3) {
      sort_array(&buff, 2);
      send(ns, &buff, sizeof(buff), 0);
    }
    else if(opt == 4) {
      split_array(&buff);
      send(ns, &buff, sizeof(buff), 0);
    }
    else break;
  }
  printf("\n");
  
  close(ns);
  close(s);
}

int search_array(int search_val, int array[]) {
  int i;
  for(i = 0; i < 5; i++) {
    if(array[i] == search_val)
      return i;
  }
  return -1;
}

void sort_array(int array[], int opt) {
  if (opt == 1) // ascending order
  {
    int i, j, c = 0;
    
    for(i = 0; i < 5; i++) {
      for(j = 0; j < 4 - i; j++) {
        if(array[j] >= array[j + 1]) {
          int temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
          c = 1;
        }
      }
      if(c == 0)
        break;
    }
  }

  if(opt == 2) //descending order
  {
    int i, j, c = 0;
    
    for(i = 0; i < 5; i++) {
      for(j = 0; j < 5 - i; j++) {
        if(array[j] < array[j + 1]) {
          int temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
          c = 1;
        }
      }
      if(c == 0)
        break;
    }
  }
}

void split_array(int array[]) {
  int even_array[5], odd_array[5];
  int e_c = 0, o_c = 0, i;

  for(i = 0; i < 5; i++) {
    if(array[i] % 2 == 0) 
      even_array[e_c++] = array[i];
    else odd_array[o_c++] = array[i];
  }

  for(i = 0; i < e_c; i++)
    array[i] = even_array[i];

  for(i = e_c; i < 5; i++)
    array[i] = odd_array[i - e_c];
}
