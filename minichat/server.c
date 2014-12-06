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
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include "wrsock.h"

#define DEBUG 1
struct sockaddr_in *autre[100]; /* Table des clients qui ont contacte
                                    le serveur */
int len = sizeof(struct sockaddr_in);
 
void TraitementClavier(int sock) { /* Socket E/S */
  char buf[256];
  int taillemessage;
  int  i;
         
  taillemessage=read(0, buf, 256);               
  for (i=0; i< 100; i++)
    if (autre[i]) { /* Si un client est enregistre */
      /* Envoyer a tous les client la taille du message puis le message */
      sendto(sock,&taillemessage, sizeof(taillemessage), 0,
	     (struct sockaddr *)autre[i], sizeof(struct sockaddr));
      
      sendto(sock,buf, taillemessage, 0, 
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
  char buf[256];
  u_short numappelant;
  int taillemessage;
  int i;
  socklen_t len;
  struct sockaddr_in *appellant= (struct sockaddr_in *) 
    malloc(sizeof(struct sockaddr_in));
  
   len = sizeof(struct sockaddr_in);
  /* Le client commance par envoyer la taille du message : que le serveur recupere */
  /* On recupère aussi dans appellant l'adresse du client */
  recvfrom(sock, &taillemessage, sizeof(taillemessage), 0, 
	   (struct sockaddr *) appellant, &len);
  
 
printf("taille = %d\n", len);
    
  printf("direct port appelant = %d\n",appellant->sin_port);
  numappelant=ntohs(appellant->sin_port)-2000;
#ifdef DEBUG
  printf("port appelant = %d\n", numappelant);
#endif

  /* Si c'est la premiere fois le client est enregistre 
   */
  if (autre[numappelant] == NULL) {
    autre[numappelant] = appellant;
  }    
  
  /* Quant toutes les information sont récupéré (l'adresse client et la taille du message)
   * On recupère le message proprement dit
   */
  recvfrom(sock, buf,  taillemessage, 0, 
	   (struct sockaddr *) NULL, NULL);

  write(1,buf, taillemessage);

  for (i=0; i< 100; i++)
    if (autre[i]) {
      /* Envoyer a tous les client la taille du message puis le message */
      sendto(sock,&taillemessage, sizeof(taillemessage), 0,
	     (struct sockaddr *)autre[i], sizeof(struct sockaddr));
      sendto(sock,buf, taillemessage, 0, 
	     (struct sockaddr *)autre[i], sizeof(struct sockaddr));
    }
  
}


/*
 * 
 */

int main(int argc, char** argv) {
  int 	sockrec;  /* Socket de reception / Emission    */
  fd_set 	readf;    /* L'esemble de descripteur d'entree */
  int 	i;
  
  
  /* Initialisation des client (au depart aucun)
   * Il faut amélioré (par liste chaînée ou autre (ne pas mettre 100 ici)
   */
  for (i=0; i< 100; i++) autre[i] = NULL; 
  
  /* Le service du serveur est le 2001
   */
  sockrec = SockUdp(NULL, 2001);
  
  /*
   *     autre = (struct sockaddr_in *) CreerSockAddr("ghadir", 2001);
   */
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

