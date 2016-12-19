	#include <fcntl.h>
	#include <stdio.h>
	#include <termios.h>
	#include <unistd.h>

	#define LG_BUFFER    1024

	void
setspeed (struct termios * config, speed_t vitesse)
{
	cfsetispeed (config, vitesse);
	cfsetospeed (config, vitesse);
}

	int
main (int argc, char * argv [])
{
	char *  nom_tty           = "/dev/ttyS0";
	int	vitesse           = 9600;
	int	type_parite       = 'n';
	int	nb_bits_donnees   = 8;
	int	nb_bits_arret     = 1;
	int	fd_tty            = -1;
	struct termios configuration;
	struct termios sauvegarde;

	char    buffer [LG_BUFFER];
	int     nb_lus;

	int     option;
	
	opterr = 0;
	while ((option = getopt (argc, argv, "hv:p:d:a:t:")) != -1) {
		switch (option) {
			case 'v' :
				if ((sscanf (optarg, "%d", & vitesse) != 1)
				 || (vitesse < 50) || (vitesse > 115200)) {
					fprintf (stderr, "Vitesse %s invalide \n", optarg);
					exit (1);
				}
				break;
			case 'p' :
				type_parite = optarg [0];
				if ((type_parite != 'n') && (type_parite != 'p')
				 && (type_parite != 'i')) {
					fprintf (stderr, "Parité %c invalide \n", type_parite);
					exit (1);
				}
				break;
			case 'd' :
				if ((sscanf (optarg, "%d", & nb_bits_donnees) != 1)
				 || (nb_bits_donnees < 5) || (nb_bits_donnees > 8)) {
					fprintf (stderr, "Nb bits données %d invalide \n",
							nb_bits_donnees);
					exit (1);
				}
				break;
			case 'a' :	
				if ((sscanf (optarg, "%d", & nb_bits_arret) != 1)
				 || (nb_bits_arret < 1) || (nb_bits_arret > 2)) {
					fprintf (stderr, "Nb bits arrêt %d invalide \n",
							nb_bits_arret);
					exit (1);
				}
				break;
			case 't' :
				nom_tty = optarg;
				break;
			case 'h' :
				fprintf (stderr, "Syntaxe %s [options]... \n", argv [0]);
				fprintf (stderr, "  Options : \n");
				fprintf (stderr, "     -v <vitesse en bits/seconde>  \n");
				fprintf (stderr, "     -p <parité> (n)ulle (p)aire (i)mpaire \n");
				fprintf (stderr, "     -d <bits de données> (5 à 8) \n");
				fprintf (stderr, "     -a <bits d'arrêt> (1 ou 2) \n");
				fprintf (stderr, "     -t <nom du périphérique> \n");
				exit (0);
			default :
				fprintf (stderr, "Option -h pour avoir de l'aide \n");
				exit (1);
		}
	}
	/* Ouverture non-bloquante pour basculer en mode non-local */
	fd_tty = open (nom_tty, O_RDWR | O_NONBLOCK);
	if (fd_tty < 0) {
		perror (nom_tty);
		exit (1);
	}
	if (tcgetattr (fd_tty, & configuration) != 0) {
		perror ("tcgetattr");
		exit (1);
	}
	configuration . c_cflag	&= ~ CLOCAL;
	tcsetattr (fd_tty, TCSANOW, & configuration);

	/* Maintenant ouverture bloquante en attendant CD */
	fd_tty = open (nom_tty, O_RDWR);
	if (fd_tty < 0) {
		perror (nom_tty);
		exit (1);
	}
	fprintf (stderr, "Port série ouvert \n");
	tcgetattr (fd_tty, & configuration);
	memcpy (& sauvegarde, & configuration, sizeof (struct termios));
	cfmakeraw (& configuration);
	if (vitesse < 50)
		setspeed (& configuration, B50);
	else if (vitesse < 75)
		setspeed (& configuration, B75);
	else if (vitesse < 110)
		setspeed (& configuration, B110);
	else if (vitesse < 134)
		setspeed (& configuration, B134);
	else if (vitesse < 150)
		setspeed (& configuration, B150);
	else if (vitesse < 200)
		setspeed (& configuration, B200);
	else if (vitesse < 300)
		setspeed (& configuration, B300);
	else if (vitesse < 600)
		setspeed (& configuration, B600);
	else if (vitesse < 1200)
		setspeed (& configuration, B1200);
	else if (vitesse < 1800)
		setspeed (& configuration, B1800);
	else if (vitesse < 2400)
		setspeed (& configuration, B2400);
	else if (vitesse < 4800)
		setspeed (& configuration, B4800);
	else if (vitesse < 9600)
		setspeed (& configuration, B9600);
	else if (vitesse < 19200)
		setspeed (& configuration, B19200);
	else if (vitesse < 34000)
		setspeed (& configuration, B38400);
	else if (vitesse < 57600)
		setspeed (& configuration, B57600);
	else
		setspeed (& configuration, B115200);
	switch (type_parite) {
		case 'n' :
			configuration . c_cflag &= ~ PARENB;
			break;
		case 'p' :
			configuration . c_cflag |=   PARENB;
			configuration . c_cflag &= ~ PARODD;
			break;
		case 'i':
			configuration . c_cflag |=   PARENB;
			configuration . c_cflag |=   PARODD;
			break;
	}
	configuration . c_cflag &= ~ CSIZE;
	if (nb_bits_donnees == 5)
		configuration . c_cflag |= CS5;
	else if (nb_bits_donnees == 6)
		configuration . c_cflag |= CS6;
	else if (nb_bits_donnees == 7)
		configuration . c_cflag |= CS7;
	else if (nb_bits_donnees == 8)
		configuration . c_cflag |= CS8;
	if (nb_bits_arret == 1)
		configuration .c_cflag &= ~ CSTOPB;
	else
		configuration .c_cflag |=   CSTOPB;

	/* Contrôle de flux CTS/RTS spécifique Linux */
	configuration . c_cflag |=   CRTSCTS;
	
	configuration . c_cflag &= ~ CLOCAL;
	configuration . c_cflag |=   HUPCL;
	
	if (tcsetattr (fd_tty, TCSANOW, & configuration) < 0) {
		perror ("tcsetattr");
		exit (1);
	}
	fprintf (stderr, "Port série configuré \n");

	fprintf (stderr, "Début de la réception des données \n");
	while (1) {
		nb_lus = read (fd_tty, buffer, LG_BUFFER);
		if (nb_lus < 0)  {
			perror ("read");
			exit (1);
		}
		if (nb_lus == 0)
			break;
		write (STDOUT_FILENO, buffer, nb_lus);
	}
	fprintf (stderr, "Fin de la réception des données \n");
	close (fd_tty);
	/* restauration de la configuration originale */
	fd_tty = open (nom_tty, O_RDWR | O_NONBLOCK);
	sauvegarde . c_cflag |= CLOCAL;
	tcsetattr (fd_tty, TCSANOW, & sauvegarde);
	close (fd_tty);
	return (0);
}
