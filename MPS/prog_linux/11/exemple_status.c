
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/wait.h>

	void
affiche_status (pid_t pid)
{
	FILE * fp;
	char   chaine [80];
	sprintf (chaine, "/proc/%u/status", pid);
	if ((fp = fopen (chaine, "r")) == NULL) {
		fprintf (stdout, "Processus inexistant\n");
		return;
	}
	while (fgets (chaine, 80, fp) != NULL)
		if (strncmp (chaine, "State", 5) == 0) {
			fputs (chaine, stdout);
			break;
		}
	fclose (fp);
}
	


	int
main (void)
{
	pid_t	pid;
	char	chaine [5];

	fprintf (stdout, "PID = %u\n", getpid());
	fprintf (stdout, "�tat attendu = Running\n");
	affiche_status (getpid ());
	if ((pid = fork ()) == -1) {
		perror ("fork ()");
		exit (1);
	}
	if (pid != 0) {
		sleep (5);
		fprintf (stdout, "Consultation de l'�tat de mon fils...\n");
		fprintf (stdout, "�tat attendu = Zombie\n");
		affiche_status (pid);
		fprintf (stdout, "P�re : Lecture code retour du fils...\n");
		wait (NULL);
		fprintf (stdout, "Consultation de l'�tat de mon fils...\n");
		fprintf (stdout, "�tat attendu = inexistant\n");
		affiche_status (pid);
	} else {
		fprintf (stdout, "Fils : consultation de l'�tat du p�re...\n");
		fprintf (stdout, "�tat attendu = Sleeping\n");
		affiche_status (getppid ());	
		fprintf (stdout, "Fils : Je me termine\n");
		exit (0);
	}
	fprintf (stdout, "Attente de saisie de cha�ne \n");
	fgets (chaine, 5, stdin);
	exit (0);
}
