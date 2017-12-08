#include <unistd.h>
#include <sys/wait.h>

int main(int arc, char **argv) {
     int resFils;
     int pid1,pid2;

     int tube[2];

     pipe(tube);

     pid1=fork();

     if (pid1 == 0) {
          close(tube[0]);//pas besoin du pipe en lecture
          close(1);
          dup(tube[1]);
          execlp("/home/pascalfares/mesgit/nsy103/RingOfProcess/traitement/inc","inc",NULL);
          
     }
     pid2=fork();
     if (pid2 == 0) {
          close(tube[1]);//pas besoin du pipe en ecriture
          close(0);
          dup(tube[0]);
          execlp("/home/pascalfares/mesgit/nsy103/RingOfProcess/traitement/inc","inc",NULL);
          
     }

    waitpid(pid1,(void *)&resFils,0);
    waitpid(pid2,(void *)&resFils,0);

}
