
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/wait.h>

	void	philosophe (int numero, int total, int fd);

	int
main (int argc, char * argv [])
{
	int		n;
	int		i;
	int		fd;

	if ((argc != 2) || (sscanf (argv[1], "%d", & n) != 1)) {
		fprintf (stderr, "Syntaxe : %s nb_philosophes\n", argv [0]);
		exit (1);
	}
	if ((fd = open ("essai.fcntl", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0){
		perror ("open");
		exit (1);
	}
	for (i = 0; i < n; i ++)
		write (fd, "X", 1);
	for (i = 0; i < n; i ++) {
		if (fork () != 0)
			continue;
		philosophe (i, n, fd);
		exit (0);
	}
	for (i = 0; i < n; i ++)
		wait (NULL);
	exit (0);
}



	void
philosophe (int numero, int total, int fd)
{
	struct flock	lock;
	char		nom [10];

	sprintf (nom, "FILS %d", numero);

	lock . l_type = F_WRLCK;
	lock . l_whence = SEEK_SET;
	lock . l_len = 1;

	lock . l_start = numero;
	fprintf (stderr, "%s : fourchette gauche (%ld)\n",
			 nom, lock . l_start);
	if (fcntl (fd, F_SETLKW, & lock) < 0)
		perror (nom);
	else
		fprintf (stderr, "%s : Ok\n", nom);
	
	sleep (1);	

	lock . l_start = (numero + 1) % total;
	fprintf (stderr, "%s : fourchette droite (%ld)\n", 
				nom, lock . l_start);
	if (fcntl (fd, F_SETLKW, & lock) < 0)
		perror (nom);
	else
		fprintf (stderr, "%s : Ok\n", nom);

	sleep (1);
	lock . l_type = F_UNLCK;
	fprintf (stderr, "%s : repose fourchette (%ld)\n",
				nom, lock . l_start);
	fcntl (fd, F_SETLKW, & lock);
	lock . l_start = numero;
	fprintf (stderr, "%s : repose fourchette (%ld)\n",
				nom, lock . l_start);
	fcntl (fd, F_SETLKW, & lock);
}

