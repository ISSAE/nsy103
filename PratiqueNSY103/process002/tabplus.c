#include <stdio.h>

void tabPlus(int maxi, int maxj) {

int i,j;

for(i=0; i<maxi; i++) {
         for(j=0; j<maxj; j++) {
            printf("%d+%d=%d\n",i,j,plus(i,j));
         }
      }
}
