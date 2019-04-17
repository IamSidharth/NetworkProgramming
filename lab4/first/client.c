
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int ser,cli,r;
	struct sockaddr_in server;
	ser=socket(AF_INET,SOCK_STREAM,0);
	if(ser==-1)
	{
		printf("\nerror");
	}

	int x;
	printf("Enter port number: ");
	scanf("%d",&x);

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(ser,(struct sockaddr*)&server,sizeof(server));

	char buf[50];

	buf[0]=8+'0';
	int ff=1;

	printf("\nenter 1");
	scanf("%d",&ff);

	r=send(ser,buf,sizeof(buf),0);

	close(ser);
}
