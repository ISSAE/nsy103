#include "point.h"
#include <stdio.h>
#include <stdlib.h>

Point *newPoint(int x, int y) {
      Point *res=malloc(sizeof (Point));
      res->x=x;
      res->y=y;
      return res;
}

Vecteur *newVecteur(int x, int y) {
      Vecteur *res=malloc(sizeof (Point));
      res->x=x;
      res->y=y;
      return res;
}

void translate(Point *p, Vecteur t) {
        p->x += t.x;
        p->y += t.y;
}

Point *translateF(Point p, Vecteur t) {
      Point *res=malloc(sizeof (Point));
      res->x = p.x+t.x;
      res->y = p.y + t.y;

      return res;

}

//Ceci ne marche pas
Point translateFF(Point p, Vecteur t) {
      Point res;
      res.x = p.x+t.x;
      res.y = p.y + t.y;

      return res;

}

void toStringPoint(Point *p) {
    printf("Point: {x:%d ; y:%d}",p->x,p->y);
}

void toStringVecteur(Vecteur *p) {
    printf("Point: {x:%d ; y:%d}",p->x,p->y);
}
