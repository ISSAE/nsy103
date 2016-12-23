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
    char buff[2049];
    int slen;
    

    /* Créer la socket dé change */
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Dans socket");
    }
    /* Céer l'adresse du serveur*/
    srvaddr = creerSockAddr(argv[1], atoi(argv[2]));

    if (connect(sockfd, (const struct sockaddr *) srvaddr, sizeof(*srvaddr)) < 0) {
        perror("Dasn connect ");
    }

    //TODO envoyer le nom du fochier a lire a distance (chez le serveur)
    write(sockfd,argv[3],strlen(argv[3]));
    //TODO lire le contenue du fichier complet
    //Supposons qu'un seul read suffit
    slen=read(sockfd,buff,2048);
    buff[slen]=0;
    write(1,buff,slen+1);
    close(sockfd);
  
}
