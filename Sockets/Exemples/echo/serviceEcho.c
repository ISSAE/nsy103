#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

/**
 * service prêparé pour être un thread mais aussi pourrait être appelé directement
 */
void *service(void *comm_fd) {
    int comm_sock=(intptr_t)comm_fd;
    //printf("%d", comm_sock);
    char str[100];
    int nb;
    do {
        if ((nb=read(comm_sock, str, 100)) < 0) {
            perror("read");
            exit(3);
        }
        str[nb] = 0;
        printf("[INFO] Le serveur reçoit - %s", str);
        write(comm_sock, str, nb + 1);

    } while (str[0] != '.');
    close(comm_sock);
    return 0;
}
