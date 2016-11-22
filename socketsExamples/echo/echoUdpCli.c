#include<stdio.h>
#include<sys/types.h> 
#include<netinet/in.h> 
#include<sys/socket.h> 
#include<arpa/inet.h>
#include<string.h> 
#include<unistd.h> 
#include<stdlib.h>
#include "../lib/wrsock.h"
#define PORT 7844

int main(int argc, char *argv[]) {

    int sockfd, len;

    struct sockaddr_in *serv, *cliaddr;

    char buff[2000];
    /*Creartion de la socket du client host ANY et prt ANY */
  sockfd = bindedSocket (NULL, SOCK_DGRAM, 0);
  printf("Socket biended ");
  /* autre adresse du serveur de chating */
  serv = (struct sockaddr_in *) creerSockAddr (argv[1], PORT);

  printf("Socket SRV addr préparée ");
    
    bzero(buff,0);
   
    do {
        fputs("Client : ", stdout);
        fgets(buff, sizeof (buff), stdin);
        if ((sendto(sockfd, buff, sizeof (buff), 0, (struct sockaddr *) serv, sizeof (*serv))) < 0) {
            perror("ERREUR DANS SENDTO");

        }
       if ((recvfrom(sockfd, buff, sizeof (buff), 0, (struct sockaddr *) cliaddr, &len)) < 0) {
            perror("ERROR IN RECVFROM");
            exit(0);
        }

        fputs("From Server : ", stdout);
        fputs(buff, stdout);
    } while (buff[0] != '.');

    close(sockfd);

    return 0;

}
