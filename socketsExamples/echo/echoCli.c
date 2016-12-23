#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sockfd, n;
    char sendline[100];
    char recvline[100];
    int taille;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);

    /* AFAIRE 1- : une IP quelconque a parti de argv[1] */
    /* AFAIRE 2- : un nom symbolique quelconque a parti de argv[1] exemple www.cofares.net */
    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

    connect(sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

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

}
