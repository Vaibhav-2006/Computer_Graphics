#include <stdio.h> 
#include<limits.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
    
#define PORT     8080 
#define MAXLINE 1024 

int main() { 
    int sockfd; 
    char* hello="10 5 8 7 3";
    char buffer[MAXLINE];  
    struct sockaddr_in     servaddr; 
     
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    bzero(&servaddr, sizeof(servaddr)); 
         
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    int n, len; 
        
    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr));  
    int numdata=0;
	int min=INT_MAX, max=INT_MIN;    
    do
	{
	bzero(&buffer,MAXLINE);
	recvfrom(sockfd, (char *)buffer, MAXLINE,  MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
	if(buffer[0]=='\n')
	break;
	buffer[n] = '\0';
	sscanf (buffer, "%d", &numdata);
	printf("%d\n",numdata); 
     if(numdata<min)
     min=numdata;
     if(numdata>max)
     max=numdata; 
	}while(buffer[0]!='\n');
	printf("The max and min are:%d %d",max,min);
    close(sockfd); 
    return 0; 
}
