/* Definition de la structure _point */
struct _point {
    int x;
    int y;
};



struct _vecteur {
  int x;
  int y;
};

//Les signature de fonctions

Point *newPoint(int x, int y);
Vecteur *newVecteur(int x, int y);
void translateNeMarchePas(struct _point p, struct _vecteur t);
void translate(struct _point *p, struct _vecteur t);
Point *translateF(struct _point p, struct _vecteur t);
Point translateFF(struct _point p, struct _vecteur t) ;
void toStringPoint(struct _point *p);
void toStringVecteur(struct _vecteur *p);
