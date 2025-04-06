#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>

#define SERV_TCP_PORT 5035
int main()
{
       int sockfd;
       struct sockaddr_in serv_addr;
       char send[1024],recv[1024];
       sockfd=socket(AF_INET,SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       printf("\nEnter the source file name : \n");
       scanf("%s",send);
       write(sockfd,send,sizeof(send));
       while(read(sockfd,recv,sizeof(recv))!=0)
       {
          printf("%s",recv);
       }
       close(sockfd);
       return 0;
}