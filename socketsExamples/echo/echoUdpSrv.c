#include<stdio.h> 
#include<sys/types.h> 
#include<netinet/in.h>
#include<sys/socket.h> 
#include<string.h> 
#include<unistd.h> 
#include<stdlib.h>

#define PORT 7844

int main(int argc, char *argv[]) {
    char buf[2000];
    int sockfd, len, a;
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Erreur création socket\n");
        exit(1);
    }
    printf("Socket UDP créé.\n");

    bzero(&servaddr, sizeof (servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr)) < 0) {
        perror("Erreur bind socket.");
        exit(2);
    }

    printf("UDP Serveur associé à Socket.\n");

    len = sizeof (cliaddr);

    do {

        bzero(buf, 2000);

        if ((a = recvfrom(sockfd, buf, sizeof (buf), 0, (struct sockaddr *) &cliaddr, &len)) < 0) {

            perror("ERREUR recvfrom");
            exit(3);

        }

        printf("reću du Client : %s", buf);


        if ((sendto(sockfd, buf, a, 0, (struct sockaddr *) &cliaddr, len)) < 0) {
            perror("Rien envoyé");

            exit(4);

        }

    } while (buf[0] != '.');

    close(sockfd);

    return 0;

}
