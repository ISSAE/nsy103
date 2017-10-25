#include "point.h"

int main () {
    Point p={10,20};
    Vecteur t={5,5};
    toStringPoint(&p);
    translate(&p,t);
    toStringPoint(&p);
}
