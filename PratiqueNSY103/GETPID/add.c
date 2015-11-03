#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* args[]) {
   int i=0;
   if (argc!=3) {
       printf("usage %s <v1> <v2>\n",args[0]);
       exit(1);
   }
   /* argc == 3 */
   int v1=atoi(args[1]);
   int v2=atoi(args[2]);

   printf("%d+%d=%d\n",v1,v2,v1+v2);
}
