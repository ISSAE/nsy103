
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <malloc.h>

	static void * pointeur_malloc		= NULL;
	static void * pointeur_realloc	= NULL;
	static void * pointeur_free		= NULL;

	static void * mon_malloc (size_t taille);
	static void * mon_realloc (void * ancien, size_t taille, void * appel);
	static void   mon_free (void * pointeur, void * appel);
	static int    verifie_pointeur (void * pointeur);

	#define RESTITUTION_POINTEURS()	__malloc_hook = pointeur_malloc; \
					__realloc_hook = pointeur_realloc; \
					__free_hook = pointeur_free;

	#define SAUVEGARDE_POINTEURS()	pointeur_malloc = __malloc_hook; \
					pointeur_realloc = __realloc_hook; \
					pointeur_free = __free_hook; 

	#define INSTALLATION_ROUTINES()	__malloc_hook = mon_malloc; \
					__realloc_hook = mon_realloc; \
					__free_hook = mon_free
	
	int
main (void)
{
	char * bloc = NULL;
	char * chaine = "chaine à copier";

	/* Installation originale */
#ifndef NDEBUG
	SAUVEGARDE_POINTEURS();
	INSTALLATION_ROUTINES();
#endif
	/* Une copie avec oubli du caractère final */
	bloc = malloc (strlen (chaine));
	if (bloc != NULL)
		strcpy (bloc, chaine);
	free (bloc);

	return (0);
}

	#define VALEUR_MAGIQUE	0x12345678L

	static void *
mon_malloc (size_t taille)
{
	void * bloc;

	RESTITUTION_POINTEURS();

	bloc = malloc (taille + 4 * sizeof(long));

	SAUVEGARDE_POINTEURS();
	INSTALLATION_ROUTINES ();

	if (bloc == NULL)
		return (NULL);
	/* et remplissage des données supplémentaires */
	* (long *) bloc = taille;
	* (long *) (bloc  + sizeof (long)) = VALEUR_MAGIQUE;
	* (long *) (bloc + taille + 2 * sizeof (long)) = VALEUR_MAGIQUE;
	* (long *) (bloc + taille + 3 * sizeof (long)) = VALEUR_MAGIQUE;

	/* on renvoie un pointeur sur le bloc réservé à l'appelant */
	return (bloc + 2 * sizeof (long));
}

	static void *
mon_realloc (void * ancien, size_t taille, void * appel)
{
	void * bloc;

	if (! verifie_pointeur (ancien)) {
		fprintf (stderr, "%p : realloc avec mauvais bloc\n", appel);
		abort();
	}

	RESTITUTION_POINTEURS();

	if (ancien != NULL)
		bloc = realloc (ancien - 2 * sizeof (long), 
				taille + 4 * sizeof(long));
	else
		bloc = malloc (taille + 4 * sizeof (long));

	SAUVEGARDE_POINTEURS();
	INSTALLATION_ROUTINES ();

	if (bloc == NULL)
		return (bloc);

	/* et remplissage des données supplémentaires */
	* (long *) bloc = taille;
	* (long *) (bloc  + sizeof (long)) = VALEUR_MAGIQUE;
	* (long *) (bloc + taille + 2 * sizeof (long)) = VALEUR_MAGIQUE;
	* (long *) (bloc + taille + 3 * sizeof (long)) = VALEUR_MAGIQUE;

	/* on renvoie un pointeur sur le bloc réservé à l'appelant */
	return (bloc + 2 * sizeof (long));
}

	static void
mon_free (void * pointeur, void * appel)
{
	long taille;
	long i;

	if (! verifie_pointeur (pointeur)) {
		fprintf (stderr, "%p : free avec mauvais bloc\n", appel);
		abort();
	}

	if (pointeur == NULL)
		return;

	RESTITUTION_POINTEURS();
	
	/* écrabouillons les données ! */
	taille = (* (long *) (pointeur - 2 * sizeof(long)));
	for (i = 0; i < taille + 4 * sizeof (long); i++)
		* (char *) (pointeur - 2 * sizeof (long) + i) = 0;
		
	/* et libérons le pointeur */
	free (pointeur - 2 * sizeof (long));
	
	SAUVEGARDE_POINTEURS();
	INSTALLATION_ROUTINES ();
}


	static int
verifie_pointeur (void * pointeur)
{
	long	taille;

	if (pointeur == NULL)
		return (1);
	if (* (long *) (pointeur - sizeof (long)) != VALEUR_MAGIQUE)
		return (0);
	taille = * (long *) (pointeur - 2 * sizeof (long));
	if (* (long *) (pointeur + taille) != VALEUR_MAGIQUE)
		return (0);
	if (* (long *) (pointeur + taille + sizeof (long)) != VALEUR_MAGIQUE)
		return (0);
	return (1);
}
