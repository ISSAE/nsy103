	#define _GNU_SOURCE /* pour stpcpy() */
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include <gdbm/dbm.h>

	static void construit_base (void);

	static char * fichier_credits = "/usr/src/linux/CREDITS";

	int
main (int argc, char * argv [])
{
	FILE * fp;
	char * fichier;
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s nom_base \n", argv [0]);
		exit (1);
	}
	fichier = (char *) malloc (strlen (argv [1]) + 5);
	strcpy (fichier, argv [1]);
	strcat (fichier, ".pag");
	if ((fp = fopen (fichier, "a")) != NULL)
		fclose (fp);
	strcpy (fichier, argv [1]);
	strcat (fichier, ".dir");
	if ((fp = fopen (fichier, "a")) != NULL)
		fclose (fp);
	free (fichier);
	if (dbminit (argv [1]) != 0) {
		perror ("dbminit");
		exit (1);
	}
	construit_base ();
	dbmclose ();
	return (0);
}		

	static void
construit_base (void)
{
	FILE *  fichier;

	char    ligne [256];
	char *  fin_ligne;
	size_t  debut_ligne;
	
	int     i = 0;
	
	char *  nom   = NULL;
	char *  email = NULL;
	char *  web   = NULL;
	char *  chaine;

	datum   cle;
	datum   donnee;

	int     retour;

	if ((fichier = fopen (fichier_credits, "r")) == NULL) {
		perror (fichier_credits);
		return;
	}
	/* Sauter l'entete */
	while (1) {
		if (fgets (ligne, 256, fichier) == NULL)
			return;
		/* Supprimer commentaires et retours-chariots */
		if ((fin_ligne = strpbrk (ligne, "\n\r#")) != NULL)
			fin_ligne [0] = '\0';
		if (strncmp (ligne, "--", 2) == 0)
			break;
	}
	while (1) {
		if (fgets (ligne, 256, fichier) == NULL)
			return;
		if ((fin_ligne = strpbrk (ligne, "\n\r#")) != NULL)
			fin_ligne [0] = '\0';
		/* Supprimer blancs en début de ligne */
		if ((debut_ligne = strspn (ligne, " \t\n\r")) != 0)
			memmove (ligne, ligne + debut_ligne, strlen (ligne + debut_ligne) + 1);
		if (strlen (ligne) == 0) {
			/* Ligne vide. Si le bloc est prêt, on le stocke */
			if (nom != NULL) {
				cle . dptr = (char *) (& i);
				cle . dsize = sizeof (int);
				/* On colle les champs bout à bout */
				donnee . dsize = 0;
				if (nom != NULL)
					donnee . dsize += strlen (nom);
				donnee . dsize ++; /* caractère nul */
				if (email != NULL)
					donnee . dsize += strlen (email);
				donnee . dsize ++;
				if (web != NULL)
					donnee . dsize += strlen (web);
				donnee . dsize ++;
				donnee . dptr = (char *) malloc (donnee . dsize);
				if (donnee . dptr != NULL) {
					memset (donnee . dptr, '\0', donnee . dsize);
					chaine = donnee . dptr;
					if (nom != NULL)
						chaine = stpcpy (chaine, nom);
					chaine ++; /* caractère nul */
					if (email != NULL)
						chaine = stpcpy (chaine, email);
					chaine ++;
					if (web != NULL)
						chaine = stpcpy (chaine, web);
					/*
					 * ENREGISTREMENT DES DONNÉES
					 */
					retour = store (cle, donnee);
					if (retour < 0)
						perror ("store");
					if (retour > 0)
						fprintf (stderr, "Doublon\n");
					free (donnee . dptr);
					donnee . dptr = NULL;
				}	
				i ++;
			}
			/* On libère les chaînes allouée */
			if (nom != NULL)
				free (nom);
			if (email != NULL)
				free (email);
			if (web != NULL)
				free (web);
			nom   = NULL;
			email = NULL;
			web   = NULL;
			continue;
		}
		if (strncmp (ligne, "N: ", 3) == 0) {
			if (nom == NULL) {
				if ((nom = malloc (strlen (ligne) - 2)) != NULL)
					strcpy (nom, & (ligne [3]));
				continue;
			}
			chaine = realloc (nom, strlen (nom) + strlen (ligne) - 1);
			if (chaine == NULL)
				continue;
			nom = chaine;
			sprintf (nom, "%s %s", nom, & (ligne [3]));
			continue;
		}
		if (strncmp (ligne, "E: ", 3) == 0) {
			if (email == NULL) {
				if ((email = malloc (strlen (ligne) - 2)) != NULL)
					strcpy (email, & (ligne [3]));
				continue;
			}
			chaine = realloc (email, strlen (email) + strlen (ligne) - 1);
			if (chaine == NULL)
				continue;
			email = chaine;
			sprintf (email, "%s %s", email, & (ligne [3]));
			continue;
		}
		if (strncmp (ligne, "W: ", 3) == 0) {
			if (web == NULL) {
				if ((web = malloc (strlen (ligne) - 2)) != NULL)
					strcpy (web, & (ligne [3]));
				continue;
			}
			chaine = realloc (web, strlen (web) + strlen (ligne) - 1);
			if (chaine == NULL)
				continue;
			web = chaine;
			sprintf (web, "%s %s", web, & (ligne [3]));
			continue;
		}
	}
	fclose (fichier);
}
	
