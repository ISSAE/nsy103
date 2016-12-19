
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>

	void
ouverture_fichier (char * nom, char * type, int attribut, mode_t mode)
{
	int fd;

	fprintf (stderr, "%s (%s) : ", nom, type);
	fd = open (nom, attribut, mode);
	if (fd < 0) {
		perror ("");
	} else {
		fprintf (stderr, "Ok\n");
		close (fd);
	}
}

	int
main (void)
{
	ouverture_fichier ("/etc/inittab", "O_RDONLY", O_RDONLY, 0);
	ouverture_fichier ("/etc/inittab", "O_RDWR", O_RDWR, 0);
	ouverture_fichier ("essai.open", "O_RDONLY", O_RDONLY, 0);
	ouverture_fichier ("essai.open", "O_RDWR", O_RDWR, 0);
	ouverture_fichier ("essai.open", "O_RDONLY | O_CREAT, 0640",
				O_RDONLY | O_CREAT, 
				S_IRUSR | S_IWUSR | S_IRGRP);
	ouverture_fichier ("essai.open", "O_RDWR | O_CREAT | O_EXCL, 0640", 
				O_RDWR | O_CREAT | O_EXCL, 
				S_IRUSR | S_IWUSR | S_IRGRP);
	return (0);
}
	
