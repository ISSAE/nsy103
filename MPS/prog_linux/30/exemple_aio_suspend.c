	#include <aio.h>
	#include <errno.h>
	#include <stdio.h>
	#include <sys/stat.h>

	#define NB_OP	10

	int
main (int argc, char * argv [])
{
	int              fd;
	int              i;
	struct aiocb     cb [NB_OP];
	char             buffer [256] [NB_OP];
	
	struct sigevent  lio_sigev;
	struct aiocb *   lio [NB_OP];
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s fichier\n", argv [0]);
		exit (1);
	}
	if ((fd = open (argv [1], O_RDONLY)) < 0) {
		perror ("open");
		exit (1);
	}
	for (i = 0; i < NB_OP; i ++) {
		cb [i] . aio_fildes   = fd;
		cb [i] . aio_offset   = 0;
		cb [i] . aio_buf      = buffer [i];
		cb [i] . aio_nbytes   = 256;
		cb [i] . aio_reqprio  = NB_OP - i;
		cb [i] . aio_lio_opcode = LIO_READ;
		cb [i] . aio_sigevent . sigev_notify = SIGEV_NONE;
		lio [i] = & cb [i];
	}

	lio_sigev . sigev_notify = SIGEV_NONE;
	if (lio_listio (LIO_NOWAIT, lio, NB_OP, & lio_sigev) < 0) {
		perror ("lio_listio");
		exit (1);
	}
	fprintf (stdout, "Lectures lancées\n");

	while (1) {
		for (i = 0; i < NB_OP; i ++)
			if (lio [i] != NULL)
				break;
		if (i == NB_OP)
			/* Toutes les opérations sont finies */
			break;
		if (aio_suspend (lio, NB_OP, NULL) == 0) {
			for (i = 0; i < NB_OP; i ++)
				if (lio [i] != NULL)
					if (aio_error (lio [i]) != EINPROGRESS) {
						fprintf (stdout, "Lecture %d : %d octets \n",
								i, aio_return (lio [i]));
						lio [i] = NULL;
					}
		}
	}
	return (0);
}
	
