#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "wrsock.h"
#include "traitement.h"

int main(int argc, char **argv) {
    int sockfd;
    /*pour l'adresse ip du serveur*/
    struct sockaddr_in *srvaddr;
    /* taille de la reponse */
    char buff[80];
    int slen;

    /* Céer l'adresse du serveur*/
    srvaddr = creerSock(argv[1], argv[2],SOCK_STREAM,&sockfd);

    if (connect(sockfd, (const struct sockaddr *) srvaddr, sizeof(*srvaddr)) < 0) {
        perror("Dasn connect ");
    }
    slen = reads(sockfd, buff, 80);
    write(0,buff,slen);
    close(sockfd);
  
}
