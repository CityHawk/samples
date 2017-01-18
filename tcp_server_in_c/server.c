#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int csock;
    char buf[1024];
    if (sockfd < 0) {
        perror("error creating socket");
        exit(2);
    }

    struct sockaddr_in addr;
    struct sockaddr_in caddr;
    int clen = sizeof(caddr);
    addr.sin_family = AF_INET;

    /* let the system figure out our IP address */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* this is the port we will listen on */
    addr.sin_port = htons((unsigned short) 8765);

    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
        perror("ERROR on binding");

    if (listen(sockfd, 5) < 0) /* allow 5 requests to queue up */ 
        perror("ERROR on listen");

    while (1) {
        csock = accept(sockfd, (struct sockaddr *) &addr, (socklen_t *) &clen);
        if (csock < 0) perror("ERROR on accept");

        bzero(buf, 1024);
        read(csock, buf, 1024);
        printf("got %s\n", buf);
        write(csock,buf, 1024);
        close(csock);
    }
    return 0;
}
