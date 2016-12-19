	#include <stdio.h>
	#include <unistd.h>

	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>

	#include <sys/types.h>
	#include <sys/socket.h>

	int	cree_socket_stream		(const char * nom_hote,
						 const char * nom_service,
						 const char * nom_proto);
	int	affiche_adresse_socket		(int sock);
	int	serveur_tcp			(void);
	int	quitter_le_serveur		(void);
	void	traite_connexion		(int sock);

    int
cree_socket_stream (const char * nom_hote, const char * nom_service, const char * nom_proto)
{
    int sock;
    struct sockaddr_in adresse;
    struct hostent *   hostent  = NULL;
    struct servent *   servent  = NULL;
    struct protoent *  protoent = NULL;

    if (nom_hote != NULL)
	if ((hostent = gethostbyname (nom_hote)) == NULL) {
		perror ("gethostbyname");
		return (-1);
    	}

    if ((protoent = getprotobyname (nom_proto)) == NULL) {
        perror ("getprotobyname");
        return (-1);
    }
    if (nom_service != NULL)
	if ((servent = getservbyname (nom_service,
                           protoent -> p_name)) == NULL) {
		perror ("getservbyname");
		return (-1);
	}
    if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("socket");
        return (-1);
    }
    memset (& adresse, 0, sizeof (struct sockaddr_in));
    adresse . sin_family = AF_INET;
    if (servent != NULL)
	adresse . sin_port = servent -> s_port;
    else
	adresse . sin_port = htons (0);
    if (hostent != NULL)
	adresse . sin_addr . s_addr =
             ((struct in_addr *) (hostent -> h_addr)) -> s_addr;
    else
	adresse . sin_addr . s_addr = htonl (INADDR_ANY);
    if (bind (sock, (struct sockaddr *) & adresse,
                sizeof (struct sockaddr_in)) < 0) {
        close (sock);
        perror ("bind");
        return (-1);
    }
    return (sock);
}


    int
affiche_adresse_socket (int sock)
{
    struct sockaddr_in adresse;
    socklen_t          longueur;

    longueur = sizeof (struct sockaddr_in);
    if (getsockname (sock, & adresse, & longueur) < 0) {
        perror ("getsockname");
        return (-1);
    }
    fprintf (stdout, "IP = %s, Port = %u \n",
                inet_ntoa (adresse . sin_addr),
                ntohs (adresse . sin_port));
    return (0);
}


    int
serveur_tcp (void)
{
    int sock_contact;
    int sock_connectee;
    struct sockaddr_in adresse;
    socklen_t longueur;

    sock_contact = cree_socket_stream (NULL, NULL, "tcp");
    if (sock_contact < 0)
        return (-1);
    listen (sock_contact, 5);
    fprintf (stdout, "Mon adresse >> ");
    affiche_adresse_socket (sock_contact);
    while (! quitter_le_serveur ()) {
        longueur = sizeof (struct sockaddr_in);
        sock_connectee = accept (sock_contact, & adresse, & longueur);
        if (sock_connectee < 0) {
            perror ("accept");
            return (-1);
        }
        switch (fork ()) {
            case 0 : /* fils */
                close (sock_contact);
                traite_connexion (sock_connectee);
                exit (0);
            case -1 :
                perror ("fork");
                return (-1);
            default : /* père */
                close (sock_connectee);
        }
    }
    return (0);
}

	int
quitter_le_serveur (void)
{
	return (0);
}

	void
traite_connexion (int sock)
{
	struct sockaddr_in adresse;
	socklen_t          longueur;
	char               buffer [256];

	longueur = sizeof (struct sockaddr_in);
	if (getpeername (sock, & adresse, & longueur) < 0) {
		perror ("getpeername");
		return;
	}
	sprintf (buffer, "IP = %s, Port = %u \n",
			inet_ntoa (adresse . sin_addr),
			ntohs (adresse . sin_port));
	fprintf (stdout, "Connexion : locale ");
	affiche_adresse_socket (sock);
	fprintf (stdout, "          distante %s", buffer);
	write (sock, "Votre adresse : ", 16);
	write (sock, buffer, strlen (buffer));
	close (sock);
}

	int
main (int argc, char * argv [])
{
	return (serveur_tcp ());
}

