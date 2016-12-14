#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int
main (int argc, char * argv []) {
	int fd;

	char * nv_argv [] = { "./exemple_execvp", NULL };

	fprintf (stdout, "Essai d'ouverture de %s ... ", argv [0]);

	if ((fd = open (argv [0], O_WRONLY | O_APPEND)) < 0) {
		if (errno != ETXTBSY) {
			fprintf (stdout, "impossible, errno %d\n", errno);
			exit (1);
		}
		fprintf (stdout, "�chec ETXTBSY, fichier d�j� utilis�\n");
	}

	fprintf (stdout, "Ouverture de exemple_exevp en �criture ... ");

	if ((fd = open ("exemple_execvp", O_WRONLY | O_APPEND)) < 0) {
		fprintf (stdout, "impossible, errno %d\n", errno);
		exit (1);
	}

	fprintf (stdout, "ok\nTentative d'ex�cution de exemple_execvp ... ");
	execv ("./exemple_execvp", nv_argv);

	if (errno == ETXTBSY)
		fprintf (stdout, "�chec ETXTBSY fichier d�j� utilis�\n");
	else
		fprintf (stdout, "errno = %d\n", errno);
	return (1);
}
