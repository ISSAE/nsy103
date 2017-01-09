#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../lib/wrsock.h"

int main(int argc, char **argv) {
    int sockfd;
    char sendline[100];
    char recvline[100];
    int taille;
    struct sockaddr_in *servaddr;
    if (argc==1){
        servaddr=creerSock("127.0.0.1","2023",SOCK_STREAM,&sockfd);
    } else if (argc==2) {
        servaddr=creerSock(argv[1],"2023",SOCK_STREAM,&sockfd);
    } else {
        servaddr=creerSock(argv[1],argv[2],SOCK_STREAM,&sockfd);
    }

    connect(sockfd, (struct sockaddr *) servaddr, sizeof (struct sockaddr_in));

    do {
        //bzero(sendline, 100);
        //bzero(recvline, 100);
        taille = read(0, sendline, 100); /*stdin = 0 , Entree standard */
        sendline[taille]=0;
        write(sockfd, sendline, taille + 1); /* +1 pour transmettre un 0 de fin de chaine*/
        taille=read(sockfd, recvline, 100);
        recvline[taille]=0;
        printf("Nous avons reçu %s", recvline);
    } while (recvline[0]!='.');
    
    close (sockfd);

}
