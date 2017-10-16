#include<stdio.h>

/**
  * sudo apt install manpages-fr manpages-fr-extra manpages manpages-posix manpages-fr-dev manpages-posix-dev manpages-dev
  * pour installer les pages de manuel man
  */

/* signature de la fonction f pour indiquer au compilateur les types*/
int f();

int main () {

  /* faire 
   * man 3 printf
   * pour savoir comment fonctionne printf
   */

   /* ici f est une fonction que nous allons definir dans un autre fichier */
   printf("f(%d)=%d\n",10,f(10));
}


