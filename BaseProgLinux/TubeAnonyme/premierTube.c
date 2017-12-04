#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int p[2];
  char buffer[10];
  int nbc;
  pipe(p);
  if (fork() == 0) {
    // Je suis le fils
    close(p[1]); // Suprime le tube output de chez le fils
    printf("[INFO] Le pid du fils est %d\n", getpid());
    // Lire le input du tube
    nbc = read(p[0], buffer, 10);
    // Ecrire dans le standard output
    write(1, buffer, nbc);
    exit(0);
  } else {
    // je suis le père
    close(p[0]); // suprime le tube input chez le père
    printf("[INFO] Le pid du père est %d\n", getpid());
    // Lire le standard input
    // read(0,buffer,10);
    dprintf(p[1], "%d\n", getpid());
    // write(p[1], buffer, strlen(buffer));
  }
}
