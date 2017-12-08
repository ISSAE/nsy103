#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char **argv) {
     printf("nombre de param = %d %s\n", argc, argv[0]);
     printf("pid=%d,ppid=%d\n", getpid(), getppid());
     if (argc != 3) {
         printf("Besoin de deux paramètres\n");
         exit(1);
     }
     int x,y;
     x=atoi(argv[1]);
     y=atoi(argv[2]);
     printf("%d + %d = %d\n", x, y, x+y);
     exit(0);
}
