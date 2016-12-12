#ifdef DEBUG
#include <stdio.h>
#include <inttypes.h>
#endif

int applyF(int (*f)(int, int), int x, int y){
#ifdef DEBUG
    printf("Appel de applyF avec %02lx %d %d\d",(uintptr_t) f,x,y);
#endif
    return f(x,y);
}
