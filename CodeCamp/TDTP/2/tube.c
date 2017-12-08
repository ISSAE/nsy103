#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int pip[2];
char buf [256];
int n;
/* descripteur de pipe */
void pere(){
            int n=read (0,buf,255);            
            write (pip[1],buf,n); exit(0);
}

void fils() {
           read (pip[0],buf,255); 
           write(1,buf,255);
           exit(0);
}

int main() {

    pipe(pip);
    switch (fork()) {
         case -1: perror("pipe"); exit(1);
         case 0: fils();
         default: pere();
    }
}



