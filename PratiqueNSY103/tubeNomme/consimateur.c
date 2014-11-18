/* Processus lecteur */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

main() {
  int tub;
  char buf[11];
  tub = open("fictub",O_RDONLY);
  read (tub,buf,10);
  buf[10]=0;
  printf("J’ai lu %s\n", buf);
 close (tub);
 exit(0); 
}
