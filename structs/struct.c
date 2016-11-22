#include <stdio.h>

struct _collection {
    int x;
    char c;
    int t[10];
};

typedef struct _collection collection;

typedef struct _point {
  int x;
  int y;
} Point;




int main () {
    struct _collection c;   

    collection c2;

    Point p[10];

    int i;
    c.x=10;
    c.c='a';

    for (i=0; i<10; i++) c.t[i]=c.x;

    for (i=0; i<10; i++) {
         printf("c.x=%d, c.c=%c, c.t[%d]=%d\n",c.x,c.c,i,c.t[i]);
    }
}
