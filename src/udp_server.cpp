#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void udp_input(int sockfd) {
    char buf[128];
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);

    while (1) {
        ssize_t count = recvfrom(sockfd, buf, 128, MSG_WAITALL,
                                 (struct sockaddr *) &cliaddr, &clilen);
        if (count <= 0) {
            if (count == 0) {
                return;
            }
            
            fprintf(stderr, "udp read: %s\n", strerror(errno));
            return;
        }
        count = sendto(sockfd, buf, count, 0,
                       (const sockaddr *) &cliaddr, clilen);
        if (count <= 0) {
            fprintf(stderr, "udp sendto: %s\n", strerror(errno));
        }
    }
}

int create_udp_listener(int port) {
    int sockfd;

     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket"); 
        return -1;
    }

    struct sockaddr_in servaddr; 
    memset(&servaddr, 0, sizeof(servaddr)); 

    // Filling server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(port); 
      
    // Bind the socket with the server address 
    if (bind(sockfd, (const struct sockaddr *)&servaddr,  
             sizeof(servaddr)) < 0 ) { 
        perror("bind"); 
        return -2;
    }

    return sockfd;
}

