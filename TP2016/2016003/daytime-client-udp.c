/*
 * Client daytime UDP - Exemple client UDP simple
 *
 */
#include <sys/types.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <arpa/inet.h>

#define MAXBUFLEN 100
#define LINE_MAX 100

int
main(int argc, char *argv[]) {
    register int sfd;
    int addr_len;
    struct sockaddr_in server_addr;
    int numbytes;
    char buf[MAXBUFLEN];
    char usage[LINE_MAX];
    int portnumber;
    const int portnumberdefault = 13;




    /* Usage message. */
    sprintf(usage, "Utilisation: %s [numéroport ] (0 <= port_number <= 65535)\nExample: %s 1024\n", argv[0], argv[0]);

    /* Check command line arg. */
    switch (argc) {
        case 1:
            /* Pas d'argument alors port par defaut */
            portnumber = portnumberdefault;
            break;
        case 2:
            /* le port depuis l'argument */

            if (sscanf(argv[1], "%d", &portnumber) == 0)
                exit(2);
            if (!((portnumber > 0) && (portnumber < 65535)))
                exit(3);
            break;
        default:
            printf("%s", usage);
            exit(1);
    }

    /* Sequence of system calls for a UDP (connection sans étát) client:                                        */
    /*   socket()   */
    /*   sendto()   */
    /*   fcntl() pour tuning de la reception   */
    /*   recvfrom() */
    /*   close()    */

    /* Set protocol to "0" to have socket() choose the correct protocol. */
    if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(4);
    }

    /* Prepare the socket address struct. */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnumber);
    /* Envoyer à toutes les interfaces du "host" où s'execute ce processus. */
    /* server_addr.sin_addr.s_addr = INADDR_ANY; */
    /* pour une adresse IP spécifique faire  (besoin de <arpa/inet.h>). */
    inet_aton("127.0.0.1", &(server_addr.sin_addr));

    /* Metter à zero le reste de la structure sockaddr_in. */
    memset(&(server_addr.sin_zero), '\0', 8);

    addr_len = sizeof (struct sockaddr);
    /*Envoi un chaine vide juste pour demander un réponse...*/
    if ((sendto(sfd, "", 0, 0, (struct sockaddr *) &server_addr, addr_len)) < 0) {
        perror("daytimed-udp send");
        close(sfd);
        exit(5);
    }

    /* recevoir la réponse. il y a quelquechose a lire*/
    if ((numbytes = recvfrom(sfd, buf, (int) sizeof (buf), 0, (struct sockaddr *) &server_addr, &addr_len)) < 0) {
        perror("recvfrom");
        close(sfd);
        exit(7);
    }
    /* Null-terminate the message so we can print it as a string.  */
    buf[numbytes] = '\0';
    printf("%s", buf);


    /* Close the socket. */
    close(sfd);

    exit(0);
}
