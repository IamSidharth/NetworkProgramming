#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXSIZE 90
void sort(char *str)
{
    int i,j;
    for (i = 0; i < strlen(str) - 1; i++)
        for (j = 0; j < strlen(str) - i - 1; j++)
            if (str[j + 1] < str[j]) 
            {
                char t = str[j];
                str[j] = str[j + 1];
                str[j + 1] = t;
            }
}
int main()
{
	int s,r,recb,sntb,x,ns,a=0,pid,status;
	char str1[50],str2[50],data[50];
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
	while(1)
	{
		len=sizeof(client);
		ns=accept(s,(struct sockaddr*)&client, &len);
		if(ns==-1)
		{
			close(s);
			exit(0);
		}

		if (recv(ns,buff,sizeof(buff),0) == -1) 
		{
            printf("\n Error Reading Data from Socket.\n");
            close(ns);
            close(s);
            return -1;
        }        
        strcpy(str1,buff);
        printf("%s\n",str1);

        if (recv(ns,buff,sizeof(buff), 0) == -1) 
        {
            printf("\n Error Reading Data from Socket.\n");
            close(ns);
            close(s);
            return -1;
        }
        strcpy(str2,buff);
        
        printf("%s\n",str2);

        int status = 1;
        if(strlen(str1) != strlen(str2))
            status = 0;

        if(status) 
        {
        	printf("\ndadadada\n");
            //sort(str1);
            //sort(str2);
            int i = 0;
            for (i = 0; i < strlen(str1) && status; i++)
            {
            	printf("\ndadadada\n");
                if (str1[i] != str2[i])
                {
                	status = 0;
                }
            }
        }

        if(status)
        	printf("\n\nStrings are anagrams");
        else    
        	printf("\n\nStrings are not anagrams");

        close(ns);
        close(s);

	}	
}