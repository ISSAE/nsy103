#include <stdio.h>

int apply(int (*opb)(int,int), int x, int y){
    return opb(x,y);

}

int add (int x, int y) {
    return x+y;
}
int mult (int x, int y) {
    return x*y;
}

int main (int argc, char** argv) {

printf("add %d, %d = %d\n",10,10,apply(add,10,10));
printf("mult %d, %d = %d\n",10,10,apply(mult,10,10));

}
