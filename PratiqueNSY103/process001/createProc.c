#include <unistd.h>
#include <stdio.h>

main() {
   int x=0;
   int rep;
   x=10;
   rep = fork();
   printf("==== rep ===== %d\n",rep);
   if (rep > 0) {
      printf(" père x= %d", x);
      x = x+1;
      printf("Je suis le père pid=%d , ppid=%d, mon fis est %d\n", getpid(), getppid(), rep);
    printf(" père x= %d", x);
   }
   else if (rep==0) {
      printf("fils x= %d", x);
      x = x+1;
      printf("Je suis le fils pid=%d , ppid=%d, resp est %d\n", getpid(), getppid(), rep);
      printf("fils x= %d", x); 
  }
  else printf("Erreur");

}
