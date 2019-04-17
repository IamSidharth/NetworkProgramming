#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>




struct student{
	int regno;
	char name[50];
	int subjectCode[5];
	char address[50];
	char dept[10];
	int semester;
	char section;
	int marks[5];

};

int main()
{
	struct student s[100] = {[0]= { 
		1,
		"Sid",
		{111,112,113,114,115},
		"Hyd",
		"ICT",
		6,
		'B',
		{9, 9, 9, 3, 1}
	}};
	// s[0].regno=1;
	//s[0].name="Sid";
	// strcpy(s[0].name,"Sid");
	// memcpy(s[0].subjectCode,[111,112,113,114,115]);
	// s[0].address="Hyd";
	// s[0].dept="ICT";
	// s[0].semester=6;
	// s[0].section='B';
	// s[0].marks={9,9,9,3,1};


	int ser,ns,r;
	int x;
	printf("\n Enter Port Number: \n");
	scanf("%d",&x);
	struct sockaddr_in server, client;
	ser=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=bind(ser,(struct sockaddr*)&server,sizeof(server));

	r=listen(ser,1);

	int len=sizeof(client);

	ns=accept(ser,(struct sockaddr*)&client,&len);

	char buf[50];

	r=recv(ns,buf,sizeof(buf),0);
	printf("\n%c\n",buf[0]);
	int choice=buf[0]-'0';
	sprintf(choice,buf[0]);
	printf("\n Choice is: %d\n",choice);

	int pid;
	pid=fork();
	if(pid==0 && choice == 1)
	{
		printf("\nChoice 1\n");
		int i;


	}
	else if(choice==2 || choice==3)
	{
		int ppid;
		ppid=fork();
		if(ppid==0 && choice==2)
		{

		}
		else if(choice==3)//choice = 3
		{

		}

	}



}