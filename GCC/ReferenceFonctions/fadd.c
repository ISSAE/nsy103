#ifdef DEBUG
#include <stdio.h>
#endif

int fadd(int x, int y){
#ifdef DEBUG
    printf("Dans add %d %d\n",x,y);
#endif
    return x+y;
}