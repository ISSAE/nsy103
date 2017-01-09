/*Entêtes nécessaires*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../lib/wrsock.h"

int main(int argc, char **argv) {

    char str[100];
    int listen_fd, comm_fd;

    listen_fd = bindedSocket(NULL, argv[1], SOCK_STREAM);

    listen(listen_fd, 10);

    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

    do {
        bzero(str, 100);
        read(comm_fd, str, 100);
        printf("Le serveur reçoit - %s", str);
        write(comm_fd, str, strlen(str) + 1);

    } while (str[0]!='.');
    close(comm_fd);
    close(listen_fd);
}
