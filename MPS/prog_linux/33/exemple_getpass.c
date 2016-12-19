	#include <stdio.h>
	#include <unistd.h>

	int
main (void)
{
	char * chaine;
	chaine = getpass ("Mot de passe : ");
	fprintf (stdout, "Le mot de passe saisi est \"%s\" \n", chaine);
	return (0);
}
