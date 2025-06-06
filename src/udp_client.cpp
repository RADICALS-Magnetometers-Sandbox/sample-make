// Client side implementation of UDP client-server model 
#include <iostream> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT 50000 
#define MAXLINE 128 
  
// Driver code 
int main() { 
    int sockfd; 
    char buf[MAXLINE]; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n;
    socklen_t servlen; 

    while (1) {
        int count = read(0, buf, MAXLINE);
        if (count < 0) {
            perror("read");
            break;
        }
        
        if (-1 == sendto(sockfd, buf, count, 0,
                         (const struct sockaddr *) &servaddr, sizeof(servaddr))) {
            perror("sendto");
            break;
        }
        
        n = recvfrom(sockfd, buf, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *) &servaddr, &servlen); 
        std::cout<<"Server :" << buf << std::endl; 
    }

    close(sockfd); 
    return 0; 
}
