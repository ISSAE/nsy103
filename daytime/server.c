/*
 * daytimetcpsrv.c#include <unistd.h>
 *
 *  Created on: 2 avr. 2011
 *  modified : 28/11/2015
 *  Author: Pascal Fares
 *  Pour nsy103
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

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr, clientaddr;
    /*pour l'adresse ip du client*/
    char cliIP[INET_ADDRSTRLEN];
    
    char buff[80 * 100];
    time_t ticks;
    int clen;
    int bc;
    /* Céer la socket  un descripyeur d'entée/sortie */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /* initialiser la structure d'adresse de scoket IP:port famille */
    bzero(&servaddr, sizeof (struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(2013); /* daytime server port 2013*/
    bc = bind(listenfd, (const struct sockaddr *) &servaddr, sizeof (servaddr));
    if (bc < 0) {
        perror("Erreur Dans bind");
        exit(-1);
    }
    printf("Avant listen %d\n", bc);
    listen(listenfd, 5);
    printf("Apres listen\n");
    for (;;) {
        connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clen);       
        if (connfd < 0) {
            perror("Erreur Dans accept ");
            exit(-2);
        }
        inet_ntop(AF_INET, &(clientaddr.sin_addr), cliIP, INET_ADDRSTRLEN);
        printf("Apres accepte %d %s:%d %d\n", connfd, cliIP, clientaddr.sin_port, clen);
        
        /* répérer a date courante*/
        ticks = time(NULL);
        snprintf(buff, sizeof (buff), "%.24s\r\n", ctime(&ticks));
        /* transmetre la date vers la socket en d'autres termes vers le clients*/
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}

