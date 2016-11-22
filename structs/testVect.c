#include <stdio.h>
#include "vect.h"
#include <stdlib.h>

Vecteur *v;

int main () {

    //Vecteur v={10,20};
    Vecteur *v1;

    Vecteur *v2;

    v=(Vecteur *)malloc(sizeof(Vecteur));

    v->x=10;
    v->y=20; 

    v2=translate(v, 5,5);

    printf("adresse v2=%p, v2 = (%d,%d)\n",v2, v2->x,v2->y);

    //v1=translate(v1, 5,5);

    printf("adresse v2=%p v2 = (%d,%d)\n",v2, v2->x,v2->y);

    //printf("adresse v1=%p v1 = (%d,%d)\n",v1, v1->x,v1->y);

}


