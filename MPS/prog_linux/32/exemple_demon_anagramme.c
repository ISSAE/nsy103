	#define _GNU_SOURCE
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <syslog.h>

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
		syslog (LOG_ERR, "gethostbyname : %m");
		return (-1);
    	}

    if ((protoent = getprotobyname (nom_proto)) == NULL) {
	syslog (LOG_ERR, "getprotobyname : %m");
        return (-1);
    }
    if (nom_service != NULL)
	if ((servent = getservbyname (nom_service,
                           protoent -> p_name)) == NULL) {
		syslog (LOG_ERR, "getservbyname : %m");
		return (-1);
	}
    if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
	syslog (LOG_ERR, "socket : %m");
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
	syslog (LOG_ERR, "bind : %m");
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
	syslog (LOG_ERR, "getsockname : %m");
        return (-1);
    }
    syslog (LOG_INFO, "IP = %s, Port = %u",
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
    affiche_adresse_socket (sock_contact);
    while (! quitter_le_serveur ()) {
        longueur = sizeof (struct sockaddr_in);
        sock_connectee = accept (sock_contact, & adresse, & longueur);
        if (sock_connectee < 0) {
  	    syslog (LOG_ERR, "accept : %m");
            return (-1);
        }
        switch (fork ()) {
            case 0 : /* fils */
                close (sock_contact);
                traite_connexion (sock_connectee);
                exit (0);
            case -1 :
  	    	syslog (LOG_ERR, "fork : %m");
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
	char buffer [256];
	int  longueur;

	while (1) {
		longueur = read (sock, buffer, 256);
		if (longueur < 0) {
  	    	        syslog (LOG_ERR, "read : %m");
			exit (0);
		}
		if (longueur == 0)
			break;
		buffer [longueur] = '\0';
		strfry (buffer);
		write (sock, buffer, longueur);
	}
	close (sock);
}

	int
main (int argc, char * argv [])
{
	int i;
	
	chdir ("/");
	if (fork () != 0)
		exit (0);
	setsid();
	for (i = 0; i < OPEN_MAX; i ++)
		close (i);
	serveur_tcp ();
	return (0);
}

