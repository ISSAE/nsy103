#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
/**
 * Ce programme réalise en C la suite d'instructions suivante:
 * mkdir repertoire
 * ls -ld repertoire
 * rmdir repertoire
 * ls -ld repertoire
 */

int
main (void)
{
  fprintf (stderr, "Création repertoire mode rwxrwxrwx : ");
  if (mkdir ("repertoire", 0777) != 0) {
    perror ("");
    exit (1);
  }
  else {
    fprintf (stderr, "Ok\n");
  }
  /**
   * Appel de la commande ls à partir du programme
   */
  system ("ls -ld repertoire");
  fprintf (stderr, "Suppression repertoire : ");
  if (rmdir ("repertoire") != 0) {
    perror ("");
    exit (1);
  }
  else {
    fprintf (stderr, "Ok\n");
  }
  fprintf (stderr, "Modification umask\n");
  umask (0);
  fprintf (stderr, "Création repertoire mode rwxrwxrwx : ");
  if (mkdir ("repertoire", 0777) != 0) {
    perror ("");
    exit (1);
  }
  else {
    fprintf (stderr, "Ok\n");
  }
  /**
   * Appel de la commande ls à partir du programme
   */
  system ("ls -ld repertoire");
  fprintf (stderr, "Suppression repertoire : ");
  if (rmdir ("repertoire") != 0) {
    perror ("");
    exit (1);
  }
  else {
    fprintf (stderr, "Ok\n");
  }
  return (0);
}
