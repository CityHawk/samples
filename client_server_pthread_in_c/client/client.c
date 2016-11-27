#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXSTR 1024

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        perror("Failed to create socket");

    char hostname[] = "localhost";
    int port = 12345;

    struct hostent *hp;
    if ((hp = gethostbyname(hostname)) == 0) {
        perror("gethostbyname");
        exit(1);
    }

    printf("host detected %s, len is %d\n", hp->h_name, hp->h_length);

    long i = 0;
    while (1) {
        struct sockaddr_in serveraddr;

        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(port);
        memcpy(&serveraddr.sin_addr.s_addr, hp->h_addr, hp->h_length);

        char foo[MAXSTR];
        sprintf(foo, "qwerty%ld", i++);
        socklen_t length = sizeof(struct sockaddr_in);
        int n = sendto(sockfd, foo, strlen(foo),0,(struct sockaddr *) &serveraddr, length);
        if(n < 0)
            perror("Sendto ");

        printf("sent %d bytes to %s:%d \n", n, inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port));

        int o = recvfrom(sockfd, foo, 1024,0,(struct sockaddr *) &serveraddr, &length);
        if (o < 0)
            perror("recvfrom ");

        printf("%s\n", foo);
    }

    return 0;
}
