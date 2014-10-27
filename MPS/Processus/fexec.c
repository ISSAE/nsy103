#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void main (int argc, char *argv[])
{ 
  int Pid;
  int Fils,Etat;
  /*
    ----------------------------------------------------------
    On peut executer ce programme en lui passant diverses
    commandes en argument, par exemple, si l'executable est fexec :
    fexec /usr/bin/ps
    ----------------------------------------------------------
  */
  
  if (argc != 2)
    {printf(" Utilisation : %s fic. a executer ! \n", argv[0]);
    exit(1);
    }

  printf (" Je suis le processus %d je vais faire fork\n",(int) getpid());
  Pid=fork();
  switch (Pid)
    {
    case  0 : 
      printf (" Coucou ! je suis le fils %d\n",(int) getpid());
      printf (" %d : Code  remplace par %s\n",(int) getpid(), argv[1]);
      execl(argv[1], argv[1], NULL);
      printf (" %d : Erreur lors du exec \n", (int) getpid());
      exit (2);
      
    case   -1 :
      printf (" Le fork n'a pas reussi ");
      exit (3) ;
      
    default :
      /* le pere attend la fin du fils */
      printf (" Pere numero %d attend\n ",(int) getpid()); 
      Fils=wait (&Etat);
      printf ( " Le fils etait : %d ", Fils);
      printf (" ... son etat etait :%0x (hexa) \n",Etat);
      exit(0);
    }
}


