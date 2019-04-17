#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXSIZE 90
void main()
{
	int s,r,recb,sntb,x,ns,a=0,pid;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{

		printf("\nSocket creation error.");
		exit(0);
	}

	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));

	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}

	printf("\nSocket binded.");
	r=listen(s,2);//max 2 clients

	if(r==-1)
	{
		close(s);
		exit(0);
	}

	printf("\nSocket listening.");
	FILE *f;
	f=fopen("file1.txt","w");
	while(1)
	{
		len=sizeof(client);
		ns=accept(s,(struct sockaddr*)&client, &len);
		if(ns==-1)
		{
			close(s);
			exit(0);
		}
		int p=fork();
		if(p==0)//parent process
		{
			close(s);
			recb=recv(ns,buff,sizeof(buff),0);			
			fprintf(f,"\t%s\t",buff);
			break;
		}		
	}	
}