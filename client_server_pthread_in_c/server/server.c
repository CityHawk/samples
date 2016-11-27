#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include "function.h"

struct server_data {
    int sock;
    char *buf;
    struct sockaddr_in *clnt_addr;
    socklen_t len;
};

void *sendReply(void *sd_in) {
    struct server_data *sd = (struct server_data *) sd_in;

    printf("%s:%d\n", inet_ntoa(sd->clnt_addr->sin_addr), sd->clnt_addr->sin_port);
    reverse(sd->buf);
    socklen_t addrlen = sizeof(sd->clnt_addr);
    ssize_t o = sendto(sd->sock, sd->buf, strlen(sd->buf), 0, (struct sockaddr *) sd->clnt_addr, sd->len);
    if (o < 0)
        perror("ERROR in sendto");
    free(sd);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int sfd;
    int nport;
    /* struct addrinfo *s_addr, hints; */
    struct sockaddr_in srvr_addr, clnt_addr;

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
    char buf[1024];
    socklen_t addrlen;

    while (1) {
        memset(&clnt_addr,0,sizeof(clnt_addr));
        memset(buf,0,1024);
        addrlen = sizeof(clnt_addr);
        ssize_t n = recvfrom(sfd, buf, 1024, 0, (struct sockaddr *) &clnt_addr, &addrlen);
        if (n > 0) {
            pthread_t thread1;
            char *local_buf = malloc(strlen(buf));
            strcpy(local_buf, buf);
            struct sockaddr_in local_sockaddr;
            memcpy(&local_sockaddr, &clnt_addr, sizeof(clnt_addr));
            struct server_data *sd = malloc(sizeof(struct server_data));
            sd->sock = sfd;
            sd->buf = local_buf;
            sd->clnt_addr = &local_sockaddr;
            sd->len = addrlen;

            if (pthread_create(&thread1, NULL, sendReply, sd)) {
                perror("Thread creation");
            }
            /* pthread_join(thread1, NULL); */
            /* sendReply(sd); */
        } else {
            perror("Error in recvfrom");
        }
    }
    return 0;
}
