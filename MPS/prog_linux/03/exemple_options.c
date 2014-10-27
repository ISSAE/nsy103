
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

#ifdef OPTIONS_LONGUES

	 #include <getopt.h>

#endif

/***********************************************************************\
**     Définition des valeurs par défaut (éventuellement dans un .h)   **
\***********************************************************************/
 

	#define ADRESSE_SERVEUR_DEFAUT	"localhost"
	#define PORT_SERVEUR_DEFAUT	"4000"
	#define CONNEXION_AUTO_DEFAUT	0
	#define DELAI_CONNEXION_DEFAUT	4



/***********************************************************************\
**     Déclarations des routines de la suite de l'application          **
\***********************************************************************/


	void	sous_options 	  (char * ssopt, int * cnx_auto, int * delai);

	void	suite_application (char * adresse_serveur,
				   char * port_serveur,
				   int    connexion_auto,
				   int    delai_reconnexion,
				   int	  argc,
				   char * argv []);

	void	affiche_aide	  (char * nom_programme);



/***********************************************************************\
**                    Début du programme                               **
\***********************************************************************/



	int
main (int argc, char * argv [])
{

	/* 
	 * Copie des chaînes d'environnement.
	 * Il n'est pas indispensable sous Linux d'en faire une
	 * copie, mais c'est une bonne habitude pour assurer la
	 * portabilité du programme.
	 */

	char * opt_adr   = NULL;
	char * opt_srv   = NULL;
	int    opt_delai = 0;
	char * retour_getenv;

	/*
	 * Variables contenant les valeurs effectives de nos paramètres.
	 */

	static char * 	adresse_serveur = ADRESSE_SERVEUR_DEFAUT;
	static char * 	port_serveur    = PORT_SERVEUR_DEFAUT;
	int		connexion_auto  = CONNEXION_AUTO_DEFAUT;
	int		delai_connexion = DELAI_CONNEXION_DEFAUT;

	int	option;	



	/*
	 * Lecture des variables d'environnement, on code en dur ici
	 * le nom des variables, mais on pourrait aussi les regrouper
	 * (par #define) en tête de fichier.
	 */
	
	
	retour_getenv = getenv ("OPT_ADR");
	if ((retour_getenv != NULL) && (strlen (retour_getenv) != 0)) {
		opt_adr = (char *) malloc (strlen (retour_getenv) + 1);
		if (opt_adr != NULL) {
			strcpy (opt_adr, retour_getenv);
			adresse_serveur = opt_adr;
		} else {
			perror ("malloc");
			exit (1);
		}
	}

	retour_getenv = getenv ("OPT_SRV");
	if ((retour_getenv != NULL) && (strlen (retour_getenv) != 0)) {
		opt_srv = (char *) malloc (strlen (retour_getenv) + 1);
		if (opt_srv != NULL) {
			strcpy (opt_srv, retour_getenv);
			port_serveur = opt_srv;
		} else {
			perror ("malloc");
			exit (1);
		}
	}

	retour_getenv = getenv ("OPT_AUTO");
	/* Il suffit que la variable existe dans l'environnement, sa  */
        /* valeur ne nous importe pas.                                */ 
	if (retour_getenv != NULL)
		connexion_auto = 1;

	retour_getenv = getenv ("OPT_DELAI");
	if (retour_getenv != NULL)
		if (sscanf (retour_getenv, "%d", & opt_delai) == 1)
			delai_connexion = opt_delai;	

	/*
	 * On va passer maintenant à la lecture des options en ligne
	 * de commande.
	 */

	opterr = 1;

	while (1) {

	#ifdef OPTIONS_LONGUES
		int	index = 0;
		static struct option longopts [] = {
			{ "adresse",	1, 	NULL, 	'a' },
			{ "port",	1,	NULL,	'p' },
			{ "option",	1,	NULL,	'o' },
			{ "help",	0,	NULL,	'h' },
			{ NULL,		0,	NULL,	0 }
		};

		option = getopt_long (argc, argv, "a:p:o:h", longopts, & index);
	#else
		option = getopt (argc, argv, "a:p:o:h");
	#endif

		if (option == -1)
			break;

		switch (option) {

			case 'a' :
				/* On libère une éventuelle copie de chaîne */
				/* d'environnement équivalente.             */	
				if (opt_adr != NULL)
					free (opt_adr);
				opt_adr = NULL;
				adresse_serveur = optarg;
				break;

			case 'p' :
				/* idem */
				if (opt_srv != NULL)
					free (opt_srv);
				opt_srv = NULL;
				port_serveur = optarg;
				break;

			case 'o' :
				/* on va analyser les sous-options */
				sous_options (optarg, 
						& connexion_auto, 
						& delai_connexion);
				break;
			case 'h' :
				affiche_aide (argv [0]);
				exit (0);
				break;
			default :
				break;
		}
	}

	suite_application (adresse_serveur, port_serveur, 
                           connexion_auto, delai_connexion,
			   argc - optind, & (argv [optind])); 
		
	return (0);
}

	void
sous_options (char * ssopt, int * cnx_auto, int * delai)
{
	int	subopt;
	char	* chaine = ssopt;
	char	* value = NULL;
	int	val_delai;

	const char * tokens [] = {
		"auto", "nonauto", "delai", NULL
	};
	while ((subopt = getsubopt (& chaine, tokens, & value)) != -1) {
		switch (subopt) {

			case 0 : /* auto */
				* cnx_auto = 1;
				break;
			case 1 : /* nonauto */	
				* cnx_auto = 0;
				break;
			case 2 : /* delai=... */
				if (value == NULL) {
					fprintf (stderr, "délai attendu\n");
					break;
				}
				if (sscanf (value, "%d", & val_delai) != 1) {
					fprintf (stderr, "délai invalide\n");
					break;
				}
				* delai = val_delai;
				break;
		}
	}
}

	/*
	 * La suite de l'application ne fait qu'afficher
	 * les options et les arguments supplémentaires
	 */


	void
suite_application (char * adr_serveur,
		   char * port_serveur,
		   int    cnx_auto,
		   int    delai_cnx,
		   int	  argc,
		   char * argv [])
{
	int	i;

	fprintf (stdout, "Serveur : %s - %s\n", adr_serveur, port_serveur);
	fprintf (stdout, "Connexion auto : %s\n", cnx_auto ? "oui":"non");
	fprintf (stdout, "Délai : %d\n", delai_cnx);
	fprintf (stdout, "Arguments supplémentaires : ");
	for (i = 0; i < argc; i++)
		fprintf (stdout, "%s - ", argv [i]);
	fprintf (stdout, "\n");
}



	void
affiche_aide (char * nom_prog)
{

	fprintf (stderr, "Syntaxe : %s [options] [fichiers...]\n", nom_prog);
	fprintf (stderr, "Options :\n");
#ifdef OPTIONS_LONGUES
	fprintf (stderr, "  --help\n");
#endif
	fprintf (stderr, "  -h               Cet ecran d'aide\n");
#ifdef OPTIONS_LONGUES
	fprintf (stderr, "  --adresse <serveur>\n");
#endif
	fprintf (stderr, "  -a <serveur>     Adresse IP du serveur\n");
#ifdef OPTIONS_LONGUES
	fprintf (stderr, "  --port <numero_port>\n");
#endif
	fprintf (stderr, "  -p <num_port>    Numero de port TCP a contacter\n");
#ifdef OPTIONS_LONGUES
	fprintf (stderr, "  --option [sous_options]\n");
#endif
	fprintf (stderr, "  -o [sous_options]     \n");
	fprintf (stderr, "Sous-options :\n");
	fprintf (stderr, "  auto / nonauto   Connexion automatique ou non\n");
	fprintf (stderr, "  delai=<sec>      Delai entre deux connexions\n");

}
