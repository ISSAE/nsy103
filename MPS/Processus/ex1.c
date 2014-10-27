#include<stdio.h>

#include<unistd.h>

int 
main (void)
{
  int pid;

  printf ("Créatiod'unprocessus fils\n");

  pid =fork ();
  /* Créatio�de lacopieduprocessuscourant(fils) 
    if(pid <0)
    
    {
       			// Si fork() a échoué      
	printf ("Erreur : fork() !\n");
      return  -1;
    
  pid � �== 0)
    {
       			// Si on est dans le processus fils ...  
	      printf ("Je suis le fils\n");

        }
       
  else
    {
       			// Si on est dans le père 
	      printf ("Je suis le père\n");
         }

    return  0;
 }
