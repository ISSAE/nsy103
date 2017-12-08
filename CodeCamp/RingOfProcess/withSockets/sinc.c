#include "../lib/wrsock.h"
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv) {
    //Créer la socket d'écoute
    struct sockaddr_in addrin;
    struct sockaddr_in sin;
    struct sockaddr_in *successeur;
    socklen_t len = sizeof(sin);
    int sockIn;
    int sockOut;
     int resFils;
     int pid1;



    int sock=bindedSocket("0.0.0.0", NULL,SOCK_STREAM,&addrin);

    if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
    perror("getsockname");
    else {
      printf("%d , %s\n",ntohs(sin.sin_port), inet_ntoa(sin.sin_addr));
      printf("%s",getNameInfo(&sin));
    }

    listen(sock, 1);

    sockIn=accept(sock, (struct sockaddr *)&sin, &len); 
    successeur = creerSock("adresse ip de mon sucxcesseur","port de mon succeseur", SOCK_STREAM, &sockOut);
    connect(sockOut,successeur, len)

     pid1=fork();

     if (pid1 == 0) {      
          close(0);
          dup(sockIn);

          close(1);
          dup(sockOut);
          execlp("/home/pascalfares/mesgit/nsy103/RingOfProcess/traitement/inc","inc",NULL);          
     }
     waitpid(pid1,(void *)&resFils,0);
    

}
