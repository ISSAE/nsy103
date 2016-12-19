
	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/mman.h>

	#define TAILLE_CHAINE	128

	void *
mon_malloc_avec_mmap (size_t taille)
{
	void * retour;
	retour = mmap (NULL, taille, PROT_READ | PROT_WRITE, 
			MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (retour == MAP_FAILED)
		return (NULL);
	return (retour);
}

	void
gestionnaire_sigsegv (int numero)
{
	fprintf (stderr, "Signal SIGSEGV reçu\n");
}

	int
main (void)
{
	char * chaine = NULL;
	if (signal (SIGSEGV, gestionnaire_sigsegv) < 0) {
		perror ("signal");
		exit (1);
	}
	fprintf (stdout, "Allocation de %d octets\n", TAILLE_CHAINE);
	chaine = mon_malloc_avec_mmap (TAILLE_CHAINE);
	if (chaine == NULL) {
		perror ("mmap");
		exit (1);
	}
	fprintf (stdout, "Protections par défaut\n");
	fprintf (stdout, "   Ecriture ...");
	strcpy (chaine, "Ok");
	fprintf (stdout, "Ok\n");

	fprintf (stdout, "Interdiction de lecture\n");
	if (mprotect (chaine, TAILLE_CHAINE, PROT_NONE) < 0) {
		perror ("mprotect");
		exit (1);
	}

	fprintf (stdout, "   Lecture ...\n");
	fflush (stdout);
	fprintf (stdout, "%s\n", chaine);
	/* ici on doit déjà être arrêté par un signal */
	return (0);
}
