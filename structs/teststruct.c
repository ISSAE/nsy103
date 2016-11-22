#include <stdio.h>
#include <stdlib.h>

struct _p {
  int x;
  int y;
};

int main() {

struct _p p1,p2;

struct _p *p3,*p4;

p1.x=10; p1.y=20;

p3= (struct _p *)malloc(sizeof(struct _p));
p3->x=11; p3->y=21;


p2=p1;
p4=p3;
printf("p1(%d,%d) : p2(%d,%d)\n",p1.x,p1.y,p2.x,p2.y);
printf("p3(%d,%d) : p4(%d,%d)\n",p3->x,p3->y,p4->x,p4->y);

p1.x=15;p1.y=25;
p3->x=16;p3->y=26;

printf("p1(%d,%d) : p2(%d,%d)\n",p1.x,p1.y,p2.x,p2.y);
printf("p3(%d,%d) : p4(%d,%d)\n",p3->x,p3->y,p4->x,p4->y);

}


