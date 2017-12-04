/*Entêtes nécessaires*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../helper/helperSO.h"
#include "serviceEcho.h"
#include <pthread.h>
#include <stdint.h>

int main(int argc, char **argv) {

    //char str[100];
    int listen_fd, comm_fd;
    pthread_t tid;
    
    if (argc==1) {
        listen_fd = bindedSocket(NULL, "2023", SOCK_STREAM, NULL);
    }
    else listen_fd = bindedSocket(NULL, argv[1], SOCK_STREAM, NULL);

    if (listen(listen_fd, 10) < 0) {
        perror("listen");
        exit(1);
    }
    while (1) {
        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        if (comm_fd < 0) {
            perror("accept");
            exit(2);
        }
        
        pthread_create(&tid, NULL, service, (void *)(intptr_t)comm_fd);
    }
    close(listen_fd);
}
