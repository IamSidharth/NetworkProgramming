#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main()
{
    int sockfd;
    struct sockaddr_in serveraddr;
    char buff[50];

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    printf("[+]Client Creted\n");

    memset(&serveraddr,'\0',sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    printf("[+]Connected to server\n");
     
     while(1){
        printf("Client msg: \t\n");
        scanf("%s",&buff);
        send(sockfd,buff,strlen(buff),0);
        if(strcmp(buff,":exit")==0)
        {  close(sockfd);
             printf("[+]Exited");
            return;
        }
        recv(sockfd,buff,1024,0);
        printf("Server response: \t%s\n",buff);

     }
       

}
