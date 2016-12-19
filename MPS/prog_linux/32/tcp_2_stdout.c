	#include <stdio.h>
	#include <unistd.h>

	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>

	#include <sys/types.h>
	#include <sys/socket.h>

	#define LG_BUFFER	1024


	int lecture_arguments (int argc, char * argv [], struct sockaddr_in * adresse, char * protocole);

	int
main (int argc, char * argv [])
{
	int                sock;
	struct sockaddr_in adresse;
	char               buffer [LG_BUFFER];
	int                nb_lus;
	
	if (lecture_arguments (argc, argv, & adresse, "tcp") < 0)
		exit (1);
	adresse . sin_family = AF_INET;
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		perror ("socket");
		exit (1);
	}
	if (connect (sock, & adresse, sizeof (struct sockaddr_in)) < 0) {
		perror ("connect");
		exit (1);
	}
	setvbuf (stdout, NULL, _IONBF, 0);
	while (1) {
		if ((nb_lus = read (sock, buffer, LG_BUFFER)) == 0)
			break;
		if (nb_lus < 0) {
			perror ("read");
			break;
		}
		write (STDOUT_FILENO, buffer, nb_lus);
	}
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

