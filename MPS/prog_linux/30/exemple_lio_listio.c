	#include <aio.h>
	#include <errno.h>
	#include <stdio.h>
	#include <signal.h>
	#include <unistd.h>
	#include <sys/stat.h>

	#define SIGNAL_IO	(SIGRTMIN + 3)

	void
gestionnaire (int signum, siginfo_t * info, void * vide)
{
	struct aiocb * cb;
	ssize_t        nb_octets;
	if (info -> si_code == SI_ASYNCIO) {
		cb = info -> si_value . sival_ptr;
		if (aio_error (cb) == EINPROGRESS)
			return;
		nb_octets = aio_return (cb);
		fprintf (stdout, "Lecture 1 : %d octets lus \n", nb_octets);
	}
}

	void
thread (sigval_t valeur)
{
	struct aiocb * cb;
	ssize_t       nb_octets;
	cb = valeur . sival_ptr;
	if (aio_error (cb) == EINPROGRESS)
		return;
	nb_octets = aio_return (cb);
	fprintf (stdout, "Lecture 2 : %d octets lus \n", nb_octets);
}

	int
main (int argc, char * argv [])
{
	int              fd;
	struct aiocb     cb [3];
	char             buffer [256] [3];
	struct sigaction action;
	int              nb_octets;
	
	struct sigevent  lio_sigev;
	struct aiocb *   lio [3];
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s fichier\n", argv [0]);
		exit (1);
	}
	if ((fd = open (argv [1], O_RDONLY)) < 0) {
		perror ("open");
		exit (1);
	}
	action . sa_sigaction = gestionnaire;
	action . sa_flags     = SA_SIGINFO;
	sigemptyset (& action . sa_mask);
	if (sigaction (SIGNAL_IO, & action, NULL) < 0) {
		perror ("sigaction");
		exit (1);
	}

	/* Lecture 0 :  Pas de notification */
	cb [0] . aio_fildes   = fd;
	cb [0] . aio_offset   = 0;
	cb [0] . aio_buf      = buffer [0];
	cb [0] . aio_nbytes   = 256;
	cb [0] . aio_reqprio  = 0;
	cb [0] . aio_lio_opcode = LIO_READ;
	cb [0] . aio_sigevent . sigev_notify = SIGEV_NONE;

	/* Lecture 1 : Notification par signal */
	cb [1] . aio_fildes   = fd;
	cb [1] . aio_offset   = 0;
	cb [1] . aio_buf      = buffer [1];
	cb [1] . aio_nbytes   = 256;
	cb [1] . aio_reqprio  = 0;
	cb [1] . aio_lio_opcode = LIO_READ;
	cb [1] . aio_sigevent . sigev_notify = SIGEV_SIGNAL;
	cb [1] . aio_sigevent . sigev_signo  = SIGNAL_IO;
	cb [1] . aio_sigevent . sigev_value  . sival_ptr = & cb [1];
	
	/* Lecture 2 : Notification par thread */
	cb [2] . aio_fildes   = fd;
	cb [2] . aio_offset   = 0;
	cb [2] . aio_buf      = buffer [2];
	cb [2] . aio_nbytes   = 256;
	cb [2] . aio_reqprio  = 0;
	cb [2] . aio_lio_opcode = LIO_READ;
	cb [2] . aio_sigevent . sigev_notify = SIGEV_THREAD;
	cb [2] . aio_sigevent . sigev_notify_function   = thread;
	cb [2] . aio_sigevent . sigev_notify_attributes = NULL;
	cb [2] . aio_sigevent . sigev_value  . sival_ptr = & cb [2];

	/* Lancement des lectures */
	lio [0] = & cb [0];
	lio [1] = & cb [1];
	lio [2] = & cb [2];
	lio_sigev . sigev_notify = SIGEV_NONE;
	if (lio_listio (LIO_NOWAIT, lio, 3, & lio_sigev) < 0) {
		perror ("lio_listio");
		exit (1);
	}
	fprintf (stdout, "Lectures lanc�es\n");
	while ((aio_error (& cb [0]) == EINPROGRESS)
	    || (aio_error (& cb [1]) == EINPROGRESS)		
	    || (aio_error (& cb [2]) == EINPROGRESS))
		sleep (1);
	nb_octets = aio_return (& cb [0]);
	fprintf (stdout, "Lecture O : %d octets lus \n", nb_octets);
	
	return (0);
}
	
