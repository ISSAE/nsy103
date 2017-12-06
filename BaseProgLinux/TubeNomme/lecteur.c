#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/**
 * Processus de lecture par tube nommé
 */
int main() {
  char zone[11];
  int tub;
  /* ouverture du tube : nom = fictub*/
  tub = open("fictub", O_RDONLY);
  /* lecture dans le tube */
  read(tub, zone, 10);
  printf("processus lecteur du tube fictub: j’ai lu %s", zone);
  /* fermeture du tube */
}
