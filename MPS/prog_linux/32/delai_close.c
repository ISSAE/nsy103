	#include <errno.h>
	#include <stdio.h>
	#include <time.h>
	#include <unistd.h>

	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>

	#include <sys/types.h>
	#include <sys/socket.h>

	int lecture_arguments (int argc, char * argv [], struct sockaddr_in * adresse, char * protocole);

	int
main (int argc, char * argv [])
{
	int                sock;
	struct sockaddr_in adresse;
	time_t             debut;
	time_t             fin;
	
	if (lecture_arguments (argc, argv, & adresse, "tcp") < 0)
		exit (1);
	adresse . sin_family = AF_INET;
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		perror ("socket");
		exit (1);
	}
	if (bind (sock, & adresse, sizeof (struct sockaddr_in)) < 0) {
		perror ("bind");
		exit (1);
	}
	listen (sock, 5);
	close (accept (sock, NULL, 0));
	close (sock);
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		perror ("socket");
		exit (1);
	}
	time (& debut);
	while (1) {
		if (bind (sock, & adresse, sizeof (struct sockaddr_in)) == 0)
			break;
		if (errno != EADDRINUSE) {
			perror ("bind 2");
			return (-1);
		}
		sleep (1);
	}
	time (& fin);
	fprintf (stdout, "Durée de persistance après fermeture : %ld \n", fin - debut);
	return (0);
}


	int
lecture_arguments (int argc, char * argv [], struct sockaddr_in * adresse, char * protocole)
{
	char * liste_options = "a:p:h";
	int    option;
	
	char * hote  = "localhost";
	char * port = "2000";

	struct hostent * hostent;
	struct servent * servent;

	int    numero;

	while ((option = getopt (argc, argv, liste_options)) != -1) {
		switch (option) {
			case 'a' :
				hote  = optarg;
				break;
			case 'p' :
				port = optarg;
				break;
			case 'h' :
				fprintf (stderr, "Syntaxe : %s [-a adresse] [-p port] \n",
						argv [0]);
				return (-1);
			default	: 
				break;
		}
	}
	memset (adresse, 0, sizeof (struct sockaddr_in));
	if (inet_aton (hote, & (adresse -> sin_addr)) == 0) {
		if ((hostent = gethostbyname (hote)) == NULL) {
			fprintf (stderr, "hôte %s inconnu \n", hote);
			return (-1);
		}
		adresse -> sin_addr . s_addr =
			((struct in_addr *) (hostent -> h_addr)) -> s_addr; 
	}
	if (sscanf (port, "%d", & numero) == 1) {
		adresse -> sin_port = htons (numero);
		return (0);
	}
	if ((servent = getservbyname (port, protocole)) == NULL) {
		fprintf (stderr, "Service %s inconnu \n", port);
		return (-1);
	}
	adresse -> sin_port = servent -> s_port;
	return (0);
}

