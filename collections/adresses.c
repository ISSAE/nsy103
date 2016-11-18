#include <stdio.h>

int main () {

   int *t;

   int x;

   x=10;

   t = &x;


   printf("adresse = %p valeur = %d\n", t, *t);

  *t=5;

  printf("x=%d", x);

  
 printf("adresse = %p valeur = %d\n", t, t[0]);
}
