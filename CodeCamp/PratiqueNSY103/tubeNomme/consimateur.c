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
  if (unlink("fictub") < 0) {
     perror ("Unlink avant close");
  }
  sleep(60);
  printf("Apres unlink");
  read (tub,buf,10);
  buf[10]=0;
  printf("J’ai lu %s\n", buf);
  if (close (tub) < 0) {
      perror("close Apres unlink");
  }

  
 exit(0); 
}
