/*
 *   Day time tcp serv
 *
 *  Created on: 2 avr. 2011
 *  modified : 28/11/2015 : bug
 *  modified : 30/11/2015 : utilisation d'utilitaire wrsock et traitement
 *  Author: Pascal Fares
 *  Pour nsy103
 *  utiliser en faisant par exemple "telnet localhost 2013"
 */
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
    int listenfd, connfd;
    
    /* pour l'adresse ip du client*/
    char cliIP[INET_ADDRSTRLEN];
    struct sockaddr_in clientaddr;
    unsigned int clen;
    /* pour la date */
    char buff[2049];
    int tdate;
    time_t ticks;
    int fd;
    
    /* Céer la socket  d'ecoute sur le port 2013 machine ANY*/
    listenfd = bindedSocket(0, SOCK_STREAM, 2013);
    if (listenfd < 0) {
        perror ("Dans bindedSocket");
        exit(1);
    }
    listen(listenfd, 5);
    for (;;) {
        connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clen);       
        if (connfd < 0) {
            perror("Erreur Dans accept ");
            exit(-2);
        }
        /* Pour information : l'adresse du client qui nous a contaté */
        inet_ntop(AF_INET, &(clientaddr.sin_addr), cliIP, INET_ADDRSTRLEN);
        printf("Le client est %s:%d \n", cliIP, clientaddr.sin_port);
        
        //TODO lire depuis le client le nom du fichier
        clen=read(connfd,buff,2048);
        buff[clen]=0;
        printf("Le fichier a lire est %s", buff);

        //TODO lire le fichier et lénvoyer au client
        //suposons que le fichier est petit
        fd = open(buff, O_RDONLY);
        if (fd <0) {
            perror("open");
            close(connfd);
        }
        clen=read(fd, buff, 2048);
        write(connfd, buff, clen);
        close(connfd);
    }
}

