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
    
    /*pour l'adresse ip du client*/
    char cliIP[INET_ADDRSTRLEN];
    struct sockaddr_in clientaddr;
    unsigned int clen;
    /* pour la date */
    char buff[80];
    int tdate;
    time_t ticks;
    
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
        
        /* répérer la date courante*/
        ticks = time(NULL);
        tdate = date(buff, sizeof (buff), &ticks);
        /* transmetre la date vers la socket en d'autres termes vers le clients*/
        write(connfd, buff, tdate);
        close(connfd);
    }
}

