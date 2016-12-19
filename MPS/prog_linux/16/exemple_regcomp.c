
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <regex.h>

	void
affiche_syntaxe (char * nom_prog)
{
	fprintf (stderr, "Syntaxe : %s [options] motif\n", nom_prog);
	fprintf (stderr, " Options :\n");
	fprintf (stderr, "  -e : expressions régulières étendues\n");
	fprintf (stderr, "  -i : pas de différences majuscule/minuscule\n");
	fprintf (stderr, "  -s : ne pas mémoriser les sous-expressions\n");
	fprintf (stderr, "  -n : gèrer les sauts de lignes\n");
	fprintf (stderr, "  -d : début de chaîne sans saut de ligne\n");
	fprintf (stderr, "  -f : fin de chaîne sans saut de ligne\n");
}

	#define LG_MAXI	256

	int
main (int argc, char * argv [])
{

	int		option;
	char *		liste_options = "eisndf";

	int		option_regcomp = 0;
	int		option_regexec = 0;
	regex_t		motif_compile;

	int		erreur;
	char *		message_erreur;
	size_t		lg_message;

	size_t		nb_sous_chaines = 0;
	regmatch_t *	sous_chaines = NULL;	

	char		ligne [LG_MAXI];
	char		sous_chaine [LG_MAXI];
	size_t		lg_sous_chaine;
	int		i;

	opterr = 0; /* pas de message d'erreur de getopt() */
	while ((option = getopt (argc, argv, liste_options)) != -1 ){
		switch (option) {
			case 'e' :
				option_regcomp |= REG_EXTENDED;
				break;
			case 'i' :
				option_regcomp |= REG_ICASE;
				break;
			case 's' :
				option_regcomp |= REG_NOSUB;
				break;
			case 'n' :
				option_regcomp |= REG_NEWLINE;
				break;
			case 'd' :
				option_regexec |= REG_NOTBOL;
				break;
			case 'f' :
				option_regexec |= REG_NOTEOL;
				break;
			case '?' :
				affiche_syntaxe (argv [0]);
				exit (1);
		}
	}
	if (argc - optind != 1) {
		/* il manque le motif */
		affiche_syntaxe (argv [0]);
		exit (1);
	}

	erreur = regcomp (& motif_compile, argv [argc - 1], option_regcomp);
	if (erreur != 0) {
		lg_message = regerror (erreur, & motif_compile, NULL, 0);
		message_erreur = (char *) malloc (lg_message);
		if (message_erreur == NULL) {
			perror ("malloc");
			exit (1);
		}
		regerror (erreur, & motif_compile, message_erreur, lg_message);
		fprintf (stderr, "%s\n", message_erreur);
		free (message_erreur);
		exit (1);
	}

	if ((option_regcomp & REG_NOSUB) == 0) {
		nb_sous_chaines = motif_compile . re_nsub + 1;
		sous_chaines = (regmatch_t *) calloc (nb_sous_chaines,
						sizeof (regmatch_t));
		if (sous_chaines == NULL) {
			perror ("calloc");
			exit (1);
		}
	}

	while (fgets (ligne, LG_MAXI, stdin) != NULL) {

		erreur = regexec (& motif_compile, ligne, nb_sous_chaines,
				sous_chaines, option_regexec);
		if (erreur == REG_NOMATCH) {
			fprintf (stdout, "Pas de correspondance\n");
			continue;
		}
		if (erreur == REG_ESPACE) {
			fprintf (stderr, "Pas assez de mémoire\n");
			exit (1);
		}

		fprintf (stdout, "Correspondance Ok\n");

		if ((option_regcomp & REG_NOSUB) != 0)
			continue;

		for (i = 0; i < nb_sous_chaines; i ++) {
			lg_sous_chaine = sous_chaines [i] . rm_eo
				       - sous_chaines [i] . rm_so;
			strncpy (sous_chaine, 
				 ligne + sous_chaines [i].rm_so,
				 lg_sous_chaine);
			sous_chaine [lg_sous_chaine] = '\0';
			if (i == 0) 
				fprintf (stdout, "expression : %s\n",
					sous_chaine);
			else
				fprintf (stdout, "ss-expr %02d : %s\n",
					i, sous_chaine);
		}

	}

	/* Ces libérations seraient indispensables si l'on voulait
  	 * compiler un nouveau motif
	 */
	free (sous_chaines);
	sous_chaines = NULL;
	nb_sous_chaines = 0;
	regfree (& motif_compile);

	return (0);
}
