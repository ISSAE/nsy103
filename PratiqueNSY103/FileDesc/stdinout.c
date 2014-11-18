#include <stdio.h>
#include <unistd.h>
#include <errno.h>

main () {
   char tab[10];
   if (read(1, tab, 5) < 0) {
       perror("read"); 
   }
   if (write(0, tab, 5) < 0) {
      perror("write 1");
   }
   if (write(0, "xxxxx", 2) < 0) {
       perror("write 0");
   }
   write(2, "yyyyyy",  2);
   if (write(3, "zzzzz",  2) < 0) {
      perror ("write 3");
   }
   printf("\n");

}
