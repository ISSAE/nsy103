#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main (void)
{ 
  int valeur;
  valeur = fork();
  printf (" Valeur retournee par la fonction fork: %d\n", (int)valeur);
  printf ("Je suis le processus numero %d\n", (int)getpid());
}
