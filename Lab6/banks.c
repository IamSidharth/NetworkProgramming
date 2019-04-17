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

struct database{
char name[50];
char password[50];
int balance;
};

 char* getfield(char* line, int num)
{
     char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
void main()
{

int sockfd,errfd,newsockfd,portno,len,sendb,temp,f[1],d[7]={0,0,0,0,0,0,0},c[2],g[1];

g[0]=1;
int flag1=0;
int flag2=0;
int recvb;
int i,j,k;
char username[50];
char password[50];




portno = 8555;
struct sockaddr_in serveraddr,cliaddr;
serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(portno);
serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

FILE *filepointer;


struct database d1[50];

if(filepointer = fopen("db.txt", "r"))
    {

    char line[1024];
    i=0;
    while (fgets(line, 1024, filepointer))
    {  char* tmp = strdup(line);
       strcpy(d1[i].name,getfield(tmp,1));
       free(tmp);
       puts(d1[i].name);
       tmp=strdup(line);
       strcpy(d1[i].password,getfield(tmp,2));
       free(tmp);
       tmp=strdup(line);
       d1[i].balance=atoi(getfield(tmp,3));
       free(tmp);
       i++;
    }
    }
    else{
    printf("File not Found");
    }
fclose(filepointer);
sockfd = socket(AF_INET,SOCK_STREAM,0);
bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
listen(sockfd,5);
len = sizeof(cliaddr);
newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);



while(1)
{
  flag2=0;
  recv(newsockfd,username,sizeof(username),0);
  send(newsockfd,g,sizeof(g),0);
  
  
  recv(newsockfd,password,sizeof(password),0);
  send(newsockfd,g,sizeof(g),0);
  
  j=0;
  while(j<i)
  {
    if(strcmp(d1[j].name,username)==0)
      {
         printf("Found \n");
         flag1=1;
         break;
      }
    j++;
  }
  if(j==i)
    {
      printf("Name not found");
      flag1=0;
    }
 j=0;
 while(j<i)
 {
    int k = strlen(d1[j].password);
       int m=0;
       while(m<k)
        {
           if(d1[j].password[m]!=password[m]+3)
             {
                break;
             }
             m++;        
        
        }
        if(m==k && k ==strlen(password))
        {
        
           flag2 =1;
           break;
        
        }
        j++;
 }
 char sendans[50];
 strcpy(sendans,"");
 
 if(flag1==1 && flag2==1)
   {strcpy(sendans,"1)Debit 2)Credit 3)Balance 4)Exit");}
 if(flag1==1 && flag2==0)
   {strcpy(sendans,"Invalid Password");}
 if(flag1==0)
   {strcpy(sendans,"Invalid Details");}
 send(newsockfd,sendans,sizeof(sendans),0);
 recv(newsockfd,f,sizeof(f),0);       


recv(newsockfd,c,sizeof(c),0);
send(newsockfd,g,sizeof(g),0);
char ans[50];
FILE *fp; 
fp= fopen("db.txt", "w");
if(c[0]==1)
{
   if(d1[j].balance-c[1]>0)
     {
        d1[j].balance=d1[j].balance-c[1];
        for(k=0;k<i;k++)
         { 
           char po[50];
           strcpy(po,"");
           strcat(po,d1[k].name);
           strcat(po,",");
           strcat(po,d1[k].password);
           strcat(po,",");
           char st[5];
           sprintf(st,"%d",d1[k].balance);
           strcat(po,st);
           fputs(po,fp);
           fputs("\n",fp);
           fflush(fp);

          }
      strcpy(ans,"Successfully Debited");

     }
     else{

       strcpy(ans,"Balance Insufficient");
     }
}


if(c[0]==2)
{
   
        d1[j].balance=d1[j].balance+c[1];
        for(k=0;k<i;k++)
         { 
           char po[50];
           strcpy(po,"");
           strcat(po,d1[k].name);
           strcat(po,",");
           strcat(po,d1[k].password);
           strcat(po,",");
           char st[5];
           sprintf(st,"%d",d1[k].balance);
           strcat(po,st);
           fputs(po,fp);
           fputs("\n",fp);
           fflush(fp);

          }
      strcpy(ans,"Successfully Credited");

     
}
if(c[0]==3)
{
char st[5];
sprintf(st,"%d",d1[k].balance);
strcpy(ans,"");
strcpy(ans,st);

}
send(newsockfd,ans,sizeof(ans),0);
recv(newsockfd,f,sizeof(f),0);

}




}
