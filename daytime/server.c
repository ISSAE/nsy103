/*
 * daytimetcpsrv.c#include <unistd.h>
 *
 *  Created on: 2 avr. 2011
 *      Author: Pascal Fares
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include    <time.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[80 * 100];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(2013); /* daytime server port 2013*/

    bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listenfd, 5);

    for (;;) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}

