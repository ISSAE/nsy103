#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int desc;

void onintr (int x)
{
     printf("Handler onintr %d\n",x);
     close(desc);
}
int main() {
    int i;
    desc = open("/home/pascalfares/toto", O_RDWR, 0);
    if (desc < 0) perror("Pas de fchier toto\n");

    signal (SIGINT, onintr);
    i = 0;
    while (i < 5000) {
          write (desc, "abcdefg", 12);
          pause();
          i = i + 1; 
    }
    printf("fin process normal %d\n",desc);
    close (desc);
    exit (0);
}
