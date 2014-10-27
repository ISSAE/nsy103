
	#include <stdio.h>
	#include <stdlib.h>
	#include <malloc.h>

	static void * pointeur_malloc		= NULL;
	static void * pointeur_realloc	= NULL;
	static void * pointeur_free		= NULL;

	static void * mon_malloc (size_t taille, void * appel);
	static void * mon_realloc (void * ancien, size_t taille, void * appel);
	static void   mon_free (void * pointeur, void * appel);

	int
main (void)
{
	char * bloc;

	/* Installation originale */
#ifndef NDEBUG
	pointeur_malloc = __malloc_hook;
	pointeur_realloc = __realloc_hook;
	pointeur_free = __free_hook;
	__malloc_hook = mon_malloc;
	__realloc_hook = mon_realloc;
	__free_hook = mon_free;
#endif

	/* et maintenant quelques appels... */
	bloc = malloc (128);
	bloc = realloc (bloc, 256);
	bloc = realloc (bloc, 16);
	free (bloc);
	bloc = calloc (256, 4);
	free (bloc);

	return (0);
}

	
	static void *
mon_malloc (size_t taille, void * appel)
{
	void * retour;

	/* restitution des pointeurs et appel de l'ancienne routine */
	__malloc_hook = pointeur_malloc;
	__realloc_hook = pointeur_realloc;
	__free_hook = pointeur_free;
	retour = malloc (taille);

	/* Ecriture d'un message sur stderr */
	fprintf (stderr, "%p : malloc (%u) -> %p\n", appel, taille, retour);

	/* on réinstalle nos routines */
	pointeur_malloc = __malloc_hook;
	pointeur_realloc = __realloc_hook;
	pointeur_free = __free_hook;
	__malloc_hook = mon_malloc;
	__realloc_hook = mon_realloc;
	__free_hook = mon_free;
	
	return (retour);
}

	static void *
mon_realloc (void * ancien, size_t taille, void * appel)
{
	void * retour;

	/* restitution des pointeurs et appel de l'ancienne routine */
	__malloc_hook = pointeur_malloc;
	__realloc_hook = pointeur_realloc;
	__free_hook = pointeur_free;
	retour = realloc (ancien, taille);

	/* Ecriture d'un message sur stderr */
	fprintf (stderr, "%p : realloc (%p, %u) -> %p\n", 
			appel, ancien, taille, retour);

	/* on réinstalle nos routines */
	pointeur_malloc = __malloc_hook;
	pointeur_realloc = __realloc_hook;
	pointeur_free = __free_hook;
	__malloc_hook = mon_malloc;
	__realloc_hook = mon_realloc;
	__free_hook = mon_free;
	
	return (retour);
}

	static void
mon_free (void * pointeur, void * appel)
{
	/* restitution des pointeurs et appel de l'ancienne routine */
	__malloc_hook = pointeur_malloc;
	__realloc_hook = pointeur_realloc;
	__free_hook = pointeur_free;
	free (pointeur);

	/* Ecriture d'un message sur stderr */
	fprintf (stderr, "%p : free (%p)\n", appel, pointeur);

	/* on réinstalle nos routines */
	pointeur_malloc = __malloc_hook;
	pointeur_realloc = __realloc_hook;
	pointeur_free = __free_hook;
	__malloc_hook = mon_malloc;
	__realloc_hook = mon_realloc;
	__free_hook = mon_free;
}

