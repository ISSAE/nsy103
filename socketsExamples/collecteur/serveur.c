/*
	$Id: serveur.c,v 1.2 2000/07/06 09:52:41 pfares Exp $
	$Log: serveur.c,v $
	Revision 1.2  2000/07/06 09:52:41  pfares
	 Amélioration du protocole entre client et serveur (recupération du
	 port client par recvfrom
	 .

	Revision 1.1  2000/07/05 20:52:04  root
	Initial revision

 * Revision 1.2  1997/03/22  06:15:04  pascal
 * Ajout des controles et entete
 *
*/
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "../lib/wrsock.h"

struct sockaddr_in *autre[100]; /* Table des clients qui ont contacte
                                    le serveur */
int len = sizeof(struct sockaddr_in);
 
void TraitementClavier(int sock) { /* Socket E/S */
  char buf[256+1];
  int taillemessage;
  int  i;
  
  bzero(buf,257);
  /* Lire l'entrée statndart stdin=0 */       
  taillemessage=read(0, buf, 256);               
  /* Transmettre le nessage avec le 0 de fin de chaine */
  for (i=0; i< 100; i++)
    if (autre[i]) { /* Si un client est enregistre */
      sendto(sock,buf, taillemessage+1, 0, 
	     (struct sockaddr *)autre[i], sizeof(struct sockaddr));
    }  
  
}                         

/*
 * Traitement de reception sur la socket du serveur
 * On recipere dans l'ordre
 * 	=> Le numero du client
 *	=> La taille du message
 * Le message est alors trace a l'ecran (pour controle)
 * et enfin il est redistribué atous les clients connus
 *
 * Entree: sock : la socket d'ecoute
 * Sortie : NEANT
 */ 
void TraitementSock(int sock) {
  char buf[256+1];
  int numappelant;
  int taillemessage;
  int i;
  unsigned int len;
  struct sockaddr_in *appellant= (struct sockaddr_in *) 
    malloc(sizeof(struct sockaddr_in));;
  /* Le client commance par envoyer la taille du message : que le serveur recupere */
  /* On recupère aussi dans appellant l'adresse du client */
  bzero(buf,257);
  taillemessage=recvfrom(sock, buf, 257, 0, 
	   (struct sockaddr *) appellant, &len);

  numappelant=ntohs(appellant->sin_port)-2000;
#ifdef DEBUG
  printf("port appelant = %d\n", numappelant);
#endif

  /* Si c'est la premiere fois le client est enregistre 
   */
  if (autre[numappelant] == NULL) {
    autre[numappelant] = appellant;
  }    
  
  for (i=0; i< 100; i++)
    if (autre[i]) {
      /* Envoyer a tous les client la taille du message puis le message */
      sendto(sock,buf, taillemessage, 0, 
	     (struct sockaddr *)autre[i], sizeof(struct sockaddr));
    }
  
}


/*
 * 
 */

int main () {
  int 	sockrec;  /* Socket de reception / Emission    */
  fd_set 	readf;    /* L'esemble de descripteur d'entree */
  int 	i;
  
  
  /* Initialisation des client (au depart aucun)
   * Il faut amélioré (par liste chaînée ou autre (ne pas mettre 100 ici)
   */
  for (i=0; i< 100; i++) autre[i] = NULL; 
  
  /* Le service du serveur est le 2001
   */
  sockrec = bindedSocket(NULL, SOCK_DGRAM, 2001);
  
  for(;;) {
    FD_SET(sockrec, &readf);
    FD_SET(0, &readf);
    
    switch (select (sockrec+1, &readf, 0,0,0)) {
    default :
      if (FD_ISSET(0, &readf)) {          /* STDIN*/
	
	TraitementClavier(sockrec);  
      }
      else if (FD_ISSET(sockrec, &readf)) {/*SOCKET*/
	    
	TraitementSock(sockrec);
      }
      
    }
  }
}	
