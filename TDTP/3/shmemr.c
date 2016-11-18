#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define CLE 217

int main(int argc, char** argv)
{
int shmid; /* Shmem id */
char *mem; /* adresse de la shmem */

/* création shm avec la clé CLE */
if ((shmid = shmget((key_t)CLE,0,0)) ==-1){ 
     perror ("Dans shmget");
     exit (1); 
}
/* attachement /* écriture sans shm */
if ((mem = shmat(shmid,NULL,0)) == (char *)-1) { 
     perror ("shmat");
     exit(2); 
}
printf ("lu: %s\n", mem);
printf("la mem est %p\n", mem);
/* détachement du processus */
if (shmdt(mem)) { 
     perror ("shmdt");
     exit(3);
}
}
