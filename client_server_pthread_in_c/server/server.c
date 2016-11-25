#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <error.h>
#include "function.h"

int main(int argc, char *argv[]) {
    char word[] = "test";
    reverse(word);
    printf("%s\n", word);

    int sfd;
    int clnt;
    int nport;
    /* struct addrinfo *s_addr, hints; */
    struct sockaddr_in srvr_addr, clnt_addr;
    char buf[1024];

    // fill in the datastructure
    srvr_addr.sin_family = AF_INET;
    nport = htons((uint16_t) 12345);
    srvr_addr.sin_port = nport;
    srvr_addr.sin_addr.s_addr = INADDR_ANY;

    if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Failed to create socket");
    }
    if (bind(sfd, (struct sockaddr *) &srvr_addr, sizeof(srvr_addr)) == -1) {
        perror("Failed to bind socket");
    }

    printf("server: %s\n", inet_ntoa(srvr_addr.sin_addr));

    while (1) {
        socklen_t addrlen;
        memset(&clnt_addr,0,sizeof(clnt_addr));
        addrlen = sizeof(clnt_addr);
        ssize_t n = recvfrom(sfd, buf, 1024, 0, (struct sockaddr *) &clnt_addr, &addrlen);
        if (n > 0) {
            printf("%s:%d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
            printf("%s\n", buf);
            reverse(buf);
            ssize_t o = sendto(sfd, buf, strlen(buf), 0, (struct sockaddr *) &clnt_addr, addrlen);
            if (o < 0) 
                perror("ERROR in sendto");
        } else {
            perror("Error in recvfrom");
        }
    }
    return 0;
}
