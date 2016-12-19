/* ----------------------------------------
 * Dans main, on indique comment  utiliser 
 * les parametres passes sur 
 * la ligne de commande 
 * ----------------------------------------
 */
void main (int argc, char *argv[])
{
  int Nbre_de_Proc, i_fils, pid_fils;
  
  
  if (argc != 2)    /* On utilise un seul parametre */
    {
      printf(" Utilisation : %s nbre-de-processus ! \n", argv[0]);
      exit(2);
    }
  
  Nbre_de_Proc = atoi (argv [1]);  /* conversion acii -> entier */
  
  
  /* ----------------------------------------
   *  creation des  processus fils   
   * ----------------------------------------
   */
  for ( i_fils =1; i_fils <=Nbre_de_Proc   ; i_fils++ )
    {
      pid_fils = fork();
      switch (pid_fils) 
	{
	case 0 :
	  fils(i_fils);       /* il faut ecrire la fonction fils ... */
	  break;
	case -1 :
	  perror("Le fork n'a pas reussi ");
	  exit(33);  /* si erreur -> fin du pere ! */
	}
    }

  /* --------------------------------------------
   *  Dans la fonction pere, on utilisera le
   *  fait que wait renvoie la valeur -1 quand
   *  il n'y a plus de processus fils a attendre.
   * --------------------------------------------
   */
  pere();                   /* il faut aussi ecrire la fonction pere ... */
}
