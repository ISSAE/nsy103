	#define _BSD_SOURCE

	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <errno.h>
	#include <grp.h>

	int
main (int argc, char * argv [])
{
	gid_t	* table_gid = NULL;
	int	i;
	int	taille;
	
	if (argc < 2) {
		fprintf (stderr, "Usage %s GID ...\n", argv [0]);
		return (1);
	}

	if ((table_gid = calloc (argc - 1, sizeof (gid_t))) == NULL) {
		fprintf (stderr, "Erreur calloc, errno = %d\n", errno);
		return (1);
	}

	for (i = 1; i < argc ; i ++)
		if (sscanf (argv [i], "%u", & (table_gid [i - 1])) != 1) {
			fprintf (stderr, "GID invalide : %s\n", argv [i]);
			return (1);
		}


	if (setgroups (i - 1, table_gid) < 0) {
		fprintf (stderr, "Erreur setgroups, errno = %d\n", errno);
		return (1);
	}

	free (table_gid);

	/*
         * Passons maintenant � la v�rification des groupes
	 */	
	
	fprintf (stdout, "V�rification : ");

	/* m�me code que la fonction main() de exemple_getgroups.c */
		
	if ((taille = getgroups (0, NULL)) < 0) {
                fprintf (stderr, "Erreur getgroups, errno = %d\n", errno);
                return (1);
        }

        if ((table_gid = calloc (taille, sizeof (gid_t))) == NULL) {
                fprintf (stderr, "Erreur  calloc, errno = %d\n", errno);
                return (1);
        }

        if (getgroups (taille, table_gid) < 0) {
                fprintf (stderr, "Erreur getgroups, errno = %d\n", errno);
                return (1);
        }
        for (i = 0; i < taille; i ++)
                fprintf (stdout, "%u ", table_gid [i]);
        fprintf (stdout, "\n");

        free (table_gid);

	return (0);
}
