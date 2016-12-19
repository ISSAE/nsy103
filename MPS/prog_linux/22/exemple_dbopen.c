	#include <db1/db.h>
	#include <fcntl.h>
	#include <limits.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/types.h>

	void traite_get (DB * db);
	void traite_put (DB * db);
	void traite_del (DB * db);
	void traite_seq (DB * db);
	
	int
main (int argc, char * argv [])
{
	DB *	db;
	DBTYPE	dbtype;
	char	saisie [128];

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s fichier type\n", argv [0]);
		return (1);
	}
	if (strcasecmp (argv [2], "btree") == 0)
		dbtype = DB_BTREE;
	else if (strcasecmp (argv [2], "hash") == 0)
		dbtype = DB_HASH;
	else if (strcasecmp (argv [2], "recno") == 0)
		dbtype = DB_RECNO;
	else {
		fprintf (stderr, "Types bases : btree, hash ou recno\n");
		return (1);
	}
	db = dbopen (argv [1], O_CREAT | O_RDWR, 0644, dbtype, NULL);
	if (db == NULL) {
		perror ("dbopen");
		return (1);
	}
	fprintf (stdout, "[commande] ");
	while (fgets (saisie, 128, stdin) != NULL) {
		if (saisie [strlen (saisie) - 1] == '\n')
		saisie [strlen (saisie) - 1] = '\0';
		if (strcasecmp (saisie, "get") == 0)
			traite_get (db);
		else if (strcasecmp (saisie, "put") == 0)
			traite_put (db);
		else if (strcasecmp (saisie, "del") == 0)
			traite_del (db);
		else if (strcasecmp (saisie, "seq") == 0)
			traite_seq (db);
		else if (strncasecmp (saisie, "quit", 4) == 0)
			break;
		else
			fprintf (stdout, "Commandes : put, get, del, seq ou quit\n");
		fprintf (stdout, "[commande] ");
	}

	db -> close (db);
	return (0);
}

	void
traite_get (DB * db)
{
	DBT	key;
	DBT	data;
	char	cle [128];
	char *	donnee;
	int	retour;

	fprintf (stdout, "[clé] ");
	if (fgets (cle, 128, stdin) == NULL) {
		fprintf (stdout, "Abandon !\n");
		return;
	}
	if (cle [strlen (cle) - 1] == '\n')
		cle [strlen (cle) - 1] = '\0';

	key . data = cle;
	key . size = strlen (cle) + 1;	/* avec '\0' */

	retour = db -> get (db, & key, & data, 0);

	if (retour < 0)
		perror ("get");
	if (retour > 0)
		fprintf (stdout, "Non trouvé\n");
	if (retour == 0) {
		donnee = (char *) malloc (data . size);
		if (donnee == NULL) {
			perror ("malloc");
			return;
		}
		memcpy (donnee, data . data, data . size);
		fprintf (stdout, "%s\n", donnee);
		free (donnee);
	}
}

	void
traite_put (DB * db)
{
	DBT	key;
	DBT	data;
	char	cle [128];
	char	donnee [128];
	int	retour;

	fprintf (stdout, "[clé] ");
	if (fgets (cle, 128, stdin) == NULL) {
		fprintf (stdout, "Abandon !\n");
		return;
	}
	if (cle [strlen (cle) - 1] == '\n')
		cle [strlen (cle) - 1] = '\0';

	key . data = cle;
	key . size = strlen (cle) + 1;

	fprintf (stdout, "[donnée] ");
	if (fgets (donnee, 128, stdin) == NULL) {
		fprintf (stdout, "Abandon !\n");
		return;
	}
	if (donnee [strlen (donnee) - 1] == '\n')
		donnee [strlen (donnee) - 1] = '\0';

	data . data = donnee;
	data . size = strlen (donnee) + 1;

	retour = db -> put (db, & key, & data, 0);
	if (retour < 0)
		perror ("put");
	else
		fprintf (stdout, "Ok\n");
}

	void
traite_del (DB * db)
{
	DBT	key;
	char	cle [128];
	int	retour;

	fprintf (stdout, "[clé] ");
	if (fgets (cle, 128, stdin) == NULL) {
		fprintf (stdout, "Abandon !\n");
		return;
	}
	if (cle [strlen (cle) - 1] == '\n')
		cle [strlen (cle) - 1] = '\0';

	key . data = cle;
	key . size = strlen (cle) + 1;	

	retour = db -> del (db, & key, 0);

	if (retour < 0)
		perror ("del");
	if (retour > 0)
		fprintf (stdout, "Non trouvé\n");
	if (retour == 0)
		fprintf (stdout, "Ok\n");
}

	void
traite_seq (DB * db)
{
	DBT	key;
	DBT	data;
	int	retour;

	for (retour = db -> seq (db, & key, & data, R_FIRST);
             retour == 0;
             retour = db -> seq (db, & key, & data, R_NEXT))
		fprintf (stdout, "%s\n    %s\n", (char *) key . data, (char *) data . data);
}

