
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/time.h>
	#include <sys/resource.h>

	void affichage_limite (char * libelle, int numero);

	int
main (void)
{
	affichage_limite ("temps CPU en secondes      ", RLIMIT_CPU);
	affichage_limite ("taille maxi d'un fichier   ", RLIMIT_FSIZE);
	affichage_limite ("taille maxi zone de données", RLIMIT_DATA);
	affichage_limite ("taille maxi de la pile     ", RLIMIT_STACK);
	affichage_limite ("taille maxi fichier core   ", RLIMIT_CORE);
	affichage_limite ("taille maxi résidente      ", RLIMIT_RSS);
	affichage_limite ("nombre maxi de processus   ", RLIMIT_NPROC);
	affichage_limite ("nombre de fichiers ouverts ", RLIMIT_NOFILE);
	affichage_limite ("taille mémoire verrouillée ", RLIMIT_NOFILE);
	return (0);
}

	void
affichage_limite (char * libelle, int numero)
{
	struct rlimit limite;
	if (getrlimit (numero, & limite) != 0) {
		fprintf (stdout, "Impossible d'accéder à la limite de %s\n",
			libelle);
		return;
	}
	fprintf (stdout, "Limite de %s : ", libelle);
	if (limite . rlim_max == RLIM_INFINITY)
		fprintf (stdout, "illimitée ");
	else
		fprintf (stdout, "%lld ", (long long int) (limite . rlim_max));
	if (limite . rlim_cur == RLIM_INFINITY)
		fprintf (stdout, "(illimitée)\n");
	else
		fprintf (stdout, "(%lld)\n", (long long int) (limite.rlim_cur));
}
