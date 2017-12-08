
#include <stdio.h>
main() {
      int i,j;
 
      for(i=0; i<10000000; i++) {
         for(j=0; j<10000000; j++) {
            printf("%d+%d=%d\n",i,j,plus(i,j));
         }
      }
}
