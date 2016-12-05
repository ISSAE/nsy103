#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 int pip[2];
 char buf [6];
 /* descripteur de pipe */
int main() {
    pipe(pip);
    switch (fork()) {
       case -1: perror("pipe"); 
                exit(1);
       case 0: fils();
               break;
       default: pere();
    }
}

void pere(){
    printf("Pere %d -> %d\n", getppid(), getpid());
    write (pip[1],"hello",5); 
    exit(0);
}
void fils() {
    printf("Fils %d -> %d\n", getppid(), getpid());
    read (pip[0],buf,5);
    buf[5]='\n'; 
    write (1, buf, 6);
    exit(0);
}
