/* $Id: client.c,v 1.2 2000/07/06 09:51:59 pfares Exp $
 * $Log: client.c,v $
 * Revision 1.2  2000/07/06 09:51:59  pfares
 * Amélioration du protocole entre client et serveur (recupération du
 * port client par recvfrom
 *
 * Revision 1.1  2000/07/05 20:51:16  root
 * Initial revision
 *
 */
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include "wrsock.h"

/* L'adresse du serveur et port 
 */
struct sockaddr_in *autre;

int len = sizeof (struct sockaddr_in);

/*
 * TraitementClavier : Lit la console (fd = 0) et transmet la chaine lu au serveur
 * ===============
 *
 * Entree : sock : la socket d'Etree/Sortie
 * Sortie  : void
 *
 * Remarque : 
 */
void 
TraitementClavier (int sock)	/* Socket E/S */
{
  char buf[256];
  int taillemessage;

  taillemessage = read(0, buf, 256);
  /* Envoyer a tous les client la taille du message puis le message */
  sendto (sock, &taillemessage, sizeof (taillemessage), 0,
	  (struct sockaddr *) autre, sizeof (struct sockaddr));

  sendto (sock, buf, taillemessage, 0,
	  (struct sockaddr *) autre, sizeof (struct sockaddr));

}

/*
 * TraitementSock  : Traitement de l'arrive d'information sur la socket
 * =============
 *
 * Entree : Sock : La socket d'E/S
 * Sortie  : void
 *
 * PSeudoCode :
 * ----------
 * Debut
 *     Lire taillemessage sur la socket d'entree en provenance du serveur 
 *     Lire message 
 *     Afficher le message a l'ecran
 * Fin
 *
 * Remarques:
 * L'adresse du serveur est definie par la variable globale autre
 */
void 
TraitementSock (int sock) {
  char buf[256];        /* Buffer de reception
			 */
  
  int  taillemessage;   /* Taille du message a recevoir
			 * Chaque emetteur commence par envoyer la taille du
			 * message
			 */
  
  /* On recoit la taile du message puis le message 
     */
  recvfrom (sock, &taillemessage, sizeof (taillemessage), 0,
	    (struct sockaddr *) NULL, NULL);

  recvfrom (sock, buf, taillemessage, 0,
	    (struct sockaddr *) NULL, NULL);

  /* Ecriture du message recu a l'ecran
   */
  write (1, buf, taillemessage);
}

/*
 * Un client possede un numero : qu'il lit dans argv                   
 * ce numero est envoyer au serveur qui l'tilisera pour repondre        
 */

int main (int argc, char **argv) {
  int sockrec;      /* Socket d'emission reception */

  fd_set readf;     /* L'ensemble de descripteur en lecture a utilise avec select */
  int num;

  if (argc != 3) {
    printf("Utilisation :  \n");
    exit(1);
  }
  num = atoi (argv[2]); /* L'identifiant client : donné par l'utilisateur */

#ifdef DEBUG
  printf ("\n : Info : Client numero => %d \n", num);
#endif
  /*Creation de la socket du client 2000+numero client */
  sockrec = SockUdp (NULL, 2000 + num);

  /* autre adresse du serveur de chating */
  autre = (struct sockaddr_in *) CreerSockAddr (argv[1], 2001);

  /* utilisation du select pour attendre une lecture de plusieurs entrés
   */
  for (;;) {
    FD_SET (sockrec, &readf);
    FD_SET (0, &readf);
    
    switch (select (sockrec + 1, &readf, 0, 0, 0)) {
    default:
      if (FD_ISSET (0, &readf)){
	TraitementClavier (sockrec);
      }
      else if (FD_ISSET (sockrec, &readf)) {
	TraitementSock (sockrec);
      }
    } /*switch*/
  }/*for*/
}/*main*/
