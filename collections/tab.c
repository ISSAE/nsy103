#include <stdio.h>

int main () {

   int t[10];
   int tab2[100];
   int i;

   for (i=0; i<100; i++) {
       t[i]=i;
   }

   for (i=0;i<10;i++) {
       printf("t[%d]=%d\n",i,t[i]);
   }

   for (i=0;i<100;i++) {
       printf("t[%d]=%d\n",i,tab2[i]);
   }

}
