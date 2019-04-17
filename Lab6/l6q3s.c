#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<ctype.h>
#include<sys/wait.h>
#include<fcntl.h> 

void main()
{

int sockfd,errfd,newsockfd,len,w[1],x[1],y[1],z[1];
x[0]=1;
int portno = 8555;
char buff[100];
char ans[50];
struct sockaddr_in serveraddr,cliaddr;

serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(portno);
serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);


sockfd = socket(AF_INET,SOCK_STREAM,0);
bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
listen(sockfd,5);
sizeof(cliaddr);
newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
recv(newsockfd,buff,sizeof(buff),0);
send(newsockfd,x,sizeof(x),0);

int pid;


FILE * fp;
fp = fopen("output.txt","w");
pid = fork();

if(pid==0)
  {   FILE *filepointer;
      filepointer=fopen(buff,"r");
      char line[1024];
      while(fgets(line, 1024, filepointer))
         {
             int i=0;
             int k = strlen(line);
             while(i<k)
             {
                line[i]=line[i]-32;
                i++;
             }
             fputs(line,fp);
             fputs("\n",fp);
             fflush(fp);

         }
       
        exit(0);
   }
else{
  wait(NULL);
   FILE *filepointer;
  filepointer=fopen(buff,"r");
  char line[1024];
      while(fgets(line, 1024, filepointer))
         {   int i=0;
             int k = strlen(line);
             while(i<k)
               {
                   line[i]=line[i]-96;
                   int k = (int)line[i];
                   char c[2];
                   sprintf(c,"%d",k);
                   fputs(c,fp);
                   i++;
                }
                fputs("\n",fp);
                fflush(fp);

         }



}
strcpy(ans,"done");
send(newsockfd,ans,sizeof(ans),0);
recv(newsockfd,x,sizeof(x),0);



close(newsockfd);
close(sockfd);

}
