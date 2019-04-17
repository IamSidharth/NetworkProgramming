#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


struct StudentInfo
{
    // char name[10] = "Japnit";
    // char regno[100] = "160953170";
    // char subjectcode[10] = "STF 6.006";
    // char addr[100] = "Room No 707, Block 13 , MIT , Manipal";
    // char enrollment[100] = "ENrolment Detals";
};


void main()
{
    int sockfd, newSockfd , ret;
    struct  sockaddr_in serveraddr , newaddr;
    char buff[1024];
    socklen_t socklen;

    pid_t childpid;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr,'\0',sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("[+]Binding done\n");

    if(listen(sockfd,10) == 0)
    printf("[+]Listening\n");
    
    
    while(1){
        newSockfd = accept(sockfd,(struct sockaddr*)&newaddr,&socklen);
        printf("[+]Connection Accepted.\n");
        if((childpid=fork()) == 0)
        {
            close(sockfd);
            while(1)
            {   
                recv(newSockfd,buff,1024,0);
                if(strcmp(buff,":exit") == 0)
                {
                    printf("[+]Disconnected");
                    break;
                }
                
                else
                {   //MOST IMPORTANT : Akanksha and Bhomika are Toppers.
                    if(strcmp(buff,"Japnit") == 0)
                     {  char retbuff[1024] = "ENrolment Detals";//should be taken from struct
                         send(newSockfd,retbuff,strlen(retbuff), 0);}
                    else if(strcmp(buff,"160953170") == 0)
                     {  char retbuff[1024] = "Japnit \t Room No 707, Block 13 , MIT , Manipal";//should be taken from struct
                         send(newSockfd,retbuff,strlen(retbuff), 0);}
                    else if(strcmp(buff,"STF 6.006")== 0)
                         {    char retbuff[1024] = "Marks = INT_MAX";//should be taken from struct
                             send(newSockfd,retbuff,strlen(retbuff), 0);}
                    else
                     send(newSockfd,buff,strlen(buff), 0);
               
                }
                
            }

            close(newSockfd);
        }
    }
    

}