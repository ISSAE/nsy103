/* 
 * File:   main.c
 * Author: pascalfares
 *
 * Created on 26 octobre 2015, 10:18
 */

#include <stdio.h>
#include <stdlib.h>

#include "point.h"

int main(int argc, char** argv) {
 /* declaration d'un point */
Point p;

 /*utilisation du point*/
 p.x=10;
 p.y=15;

 printf("(%d,%d)\n",p.x,p.y);

 Point *refp;

 refp = malloc(sizeof(struct _point));

/*
 (*refp).x=20;
 (*refp).y = 50;
*/
 refp->x=20;
 refp->y=50;

  printf("(%d,%d)\n",refp->x,refp->y);

 return (EXIT_SUCCESS);
}
