	#define	_GNU_SOURCE
	#include <search.h>
	#include <stdio.h>
	#include <string.h>

	void
ajoute_entree (char * nom, int numero, struct hsearch_data * table)
{
	ENTRY	entree;
	ENTRY * retour;

	entree . key  = strdup (nom);
	entree . data = (char *) numero;
	if (hsearch_r (entree, ENTER, & retour, table) == 0) {
		perror ("hsearch_r");
		exit (1);
	}
}

	int
main (int argc, char * argv [])
{
	struct hsearch_data	table;
	int		i;
	ENTRY	entree;
	ENTRY *	trouve;

	if (argc < 2) {
		fprintf (stderr, "Syntaxe : %s nom-dept\n", argv [0]);
		exit (1);
	}

	memset (& table, 0, sizeof (table));
	
	if (hcreate_r (100, & table) == 0) { 
		perror ("hcreate");
		exit (1);
	}

	ajoute_entree ("ain",			 1, & table);
	ajoute_entree ("aisne",			 2, & table);
	ajoute_entree ("allier",		 3, & table);
	ajoute_entree ("alpes-de-haute-provence",4, & table);
	ajoute_entree ("hautes-alpes",		 5, & table);
	ajoute_entree ("alpes-maritimes",	 6, & table);
	ajoute_entree ("ardèche",		 7, & table);
	ajoute_entree ("ardennes",		 8, & table);
	ajoute_entree ("ariège",		 9, & table);
	ajoute_entree ("aube",			10, & table);
	ajoute_entree ("aude",			11, & table);
	ajoute_entree ("aveyron",		12, & table);
	ajoute_entree ("bouches-du-rhône",	13, & table);
	ajoute_entree ("calvados",		14, & table);
	ajoute_entree ("cantal",		15, & table);
	ajoute_entree ("charente",		16, & table);
	ajoute_entree ("charente-maritime",	17, & table);
	ajoute_entree ("cher",			18, & table);
	ajoute_entree ("corrèze",		19, & table);
	ajoute_entree ("corse",			20, & table);
	ajoute_entree ("côte-d'or",		21, & table);
	ajoute_entree ("côtes-d'armor",		22, & table);
	ajoute_entree ("creuse",		23, & table);
	ajoute_entree ("dordogne",		24, & table);
	ajoute_entree ("doubs",			25, & table);
	ajoute_entree ("drôme",			26, & table);
	ajoute_entree ("eure",			27, & table);
	ajoute_entree ("eure-et-loir",		28, & table);
	ajoute_entree ("finistère",		29, & table);
	ajoute_entree ("gard",			30, & table);
	ajoute_entree ("haute-garonne",		31, & table);
	ajoute_entree ("gers",			32, & table);
	ajoute_entree ("gironde",		33, & table);
	ajoute_entree ("herault",		34, & table);
	ajoute_entree ("ille-et-vilaine",	35, & table);
	ajoute_entree ("indre",			36, & table);
	ajoute_entree ("indre-et-loire",	37, & table);
	ajoute_entree ("isere",			38, & table);
	ajoute_entree ("jura",			39, & table);
	ajoute_entree ("landes",		40, & table);
	ajoute_entree ("loir-et-cher",		41, & table);
	ajoute_entree ("loire",			42, & table);
	ajoute_entree ("haute-loire",		43, & table);
	ajoute_entree ("loire-atlantique",	44, & table);
	ajoute_entree ("loiret",		45, & table);
	ajoute_entree ("lot",			46, & table);
	ajoute_entree ("lot-et-garonne",	47, & table);
	ajoute_entree ("lozère",		48, & table);
	ajoute_entree ("maine-et-loire",	49, & table);
	ajoute_entree ("manche",		50, & table);
	ajoute_entree ("marne",			51, & table);
	ajoute_entree ("haute-marne",		52, & table);
	ajoute_entree ("mayenne",		53, & table);
	ajoute_entree ("meurthe-et-moselle",	54, & table);
	ajoute_entree ("meuse",			55, & table);
	ajoute_entree ("morbihan",		56, & table);
	ajoute_entree ("mozelle",		57, & table);
	ajoute_entree ("nièvre",		58, & table);
	ajoute_entree ("nord",			59, & table);
	ajoute_entree ("oise",			60, & table);
	ajoute_entree ("orne",			61, & table);
	ajoute_entree ("pas-de-calais",		62, & table);
	ajoute_entree ("puy-de-dome",		63, & table);
	ajoute_entree ("pyrénées-atlantique",	64, & table);
	ajoute_entree ("haute-pyrénées",	65, & table);
	ajoute_entree ("pyrénées-orientale",	66, & table);
	ajoute_entree ("bas-rhin",		67, & table);
	ajoute_entree ("haut-rhin",		68, & table);
	ajoute_entree ("rhône",			69, & table);
	ajoute_entree ("haute-saône",		70, & table);
	ajoute_entree ("saône-et-loire",	71, & table);
	ajoute_entree ("sarthe",		72, & table);
	ajoute_entree ("savoie",		73, & table);
	ajoute_entree ("haute-savoie",		74, & table);
	ajoute_entree ("paris",			75, & table);
	ajoute_entree ("seine-maritime",	76, & table);
	ajoute_entree ("seine-et-marne",	77, & table);
	ajoute_entree ("yvelines",		78, & table);
	ajoute_entree ("deux-sèvres",		79, & table);
	ajoute_entree ("somme",			80, & table);
	ajoute_entree ("tarn",			81, & table);
	ajoute_entree ("tarn-et-garonne",	82, & table);
	ajoute_entree ("var",			83, & table);
	ajoute_entree ("vaucluse",		84, & table);
	ajoute_entree ("vendee",		85, & table);
	ajoute_entree ("vienne",		86, & table);
	ajoute_entree ("haute-vienne",		87, & table);
	ajoute_entree ("vosges",		88, & table);
	ajoute_entree ("yonne",			89, & table);
	ajoute_entree ("territoire-de-belfort",	90, & table);
	ajoute_entree ("essonne",		91, & table);
	ajoute_entree ("hauts-de-seine",	92, & table);
	ajoute_entree ("seine-saint-denis",	93, & table);
	ajoute_entree ("val-de-marne",		94, & table);
	ajoute_entree ("val-d'oise",		95, & table);

	for (i = 1; i < argc; i ++) {
		entree . key = argv [i];
		fprintf (stdout, "%s -> ", argv [i]);
		if (hsearch_r (entree, FIND, & trouve, & table) == 0)
			fprintf (stdout, "pas dans la liste \n");
		else
			fprintf (stdout, "%d\n", (int) (trouve -> data));
	}
	hdestroy_r (& table);

	return (0);
}

