#ifdef DEBUG
#include <stdio.h>
#endif

int fmult(int x, int y){
#ifdef DEBUG
    printf("Dans mult %d %d\n",x,y);
#endif
    return (x*y);
}
