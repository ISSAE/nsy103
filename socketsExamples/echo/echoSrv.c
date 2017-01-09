/*Entêtes nécessaires*/

#include <sys/types.h>
#include <sys/socket.h>
 #include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../lib/wrsock.h"

int main(int argc, char **argv) {

    char str[100];
    int listen_fd, comm_fd;
    int nb;
    listen_fd = bindedSocket(NULL, argv[1], SOCK_STREAM);

    if(listen(listen_fd, 10)<0) {
        perror("listen");
        exit(1);
    }

    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    if (comm_fd<0) {
        perror("accept");
        exit(2);
    }
    do {
        
        nb=read(comm_fd, str, 100);
        if (nb<0) {
            perror("read");
            exit(3);
        }
        str[nb]=0;
        printf("Le serveur reçoit - %s", str);
        write(comm_fd, str, strlen(str) + 1);

    } while (str[0]!='.');
    close(comm_fd);
    close(listen_fd);
}
