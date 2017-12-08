/* Processus ecrivain */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

main() {

 mode_t mode;
 int tub;
 mode = S_IRUSR | S_IWUSR;
 mkfifo ("fictub",mode);
 tub = open("fictub",O_WRONLY);
 write (tub,"0123456789",10);
 close (tub);
 exit(0);
}
