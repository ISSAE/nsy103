#include "vect.h"
#include <stdio.h>
#include <stdlib.h>

Vecteur *translate (Vecteur *a, int ta, int tb) {
      Vecteur *res = (Vecteur *)malloc(sizeof(Vecteur));

      res->x=a->x+ta;
      res->y=a->y+tb;

      printf("adresse de res est %p\n", res);
      return res;

}
