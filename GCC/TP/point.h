/* Definition de la structure _point */
struct _point {
    int x;
    int y;
};

typedef struct _point Point;

typedef struct _vecteur {
  int x;
  int y;
} Vecteur;

//Les signature de fonctions

Point *newPoint(int x, int y);
Vecteur *newVecteur(int x, int y);
void translate(Point *p, Vecteur t);
Point *translateF(Point p, Vecteur t);
Point translateFF(Point p, Vecteur t) ;
void toStringPoint(Point *p);
void toStringVecteur(Vecteur *p);
