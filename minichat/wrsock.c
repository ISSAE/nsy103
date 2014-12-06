/*Ecriture sur une socket */
/*
	$Id: wrsock.c,v 2.4 2000/07/06 09:53:04 pfares Exp $ 
	$Log: wrsock.c,v $
	Revision 2.4  2000/07/06 09:53:04  pfares
	commentaires

	Revision 2.3  2000/07/05 21:35:02  root
	commentaires pour le cours reseau B.

	Revision 2.2  2000/07/05 21:09:21  root
	Avant de demarrer test de ci co cvs

 * Revision 1.2  1997/03/22  06:40:48  pascal
 * Ajout de commentaires
 *
 * Revision 1.1  1997/03/22  06:26:10  pascal
 * Initial revision
 * */
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
/******************************************************************/
/* writes : Fonction pour l'exriture en mode connecte sur un stream*/
/* INPUT:	                                                      */
/*    IN sock : identifiant d'E/S fid                             */
/*    IN pbuf : Le buffer utiliser pour l'écriture                */
/*    IN noc : Le nobre d'actets à transmettre                    */
/* OUTPUT                                                         */
/*    OUT : Le nombre d'octets rééllement envoyés ou une erreur (<0)*/
/* Description:                                                   */
/*    Dans certains cas la primitive système write n'envoie pas   */
/*    tous les actets demandés (elle retourne le nombre d'octets  */
/*    rééllement emis). On relance alors l'émisson jusqua épuisement */
/*    de tous les actets que l'on souhaite émettre                 */
/* Alogirithme:                                                    */
/*    tanque il reste des octets à emettre                         */
/*        Emmetre les octets restants                              */
/******************************************************************/
int writes(int sock, char *pbuf, int noc)
{
	int nreste, /* nombre d'octats restant à emmetre */ 
	    necrit; /* Variable qui contiendra le nb d'octets rééllement émis par write */

	/* Initialement le nb d'octets restant a éméttre est noc */	
	nreste = noc;
	while(nreste > 0)
	{ 
		necrit = write(sock, pbuf, nreste);
		/* si necrit < 0 alors pb */
		if (necrit < 0) return (necrit);
		nreste -= necrit;
		pbuf += necrit;
	}
	return(noc-nreste);
}

/******************************************************************/
/* Fonction pour la lecture en mode connecte                      */
/******************************************************************/
int reads(int sock, char *pbuf, int noc)
{
	int nreste, nlit;
	
	nreste = noc;
	while(nreste > 0)
	{ 
		nlit = read(sock, pbuf, nreste);
		if (nlit < 0) return (nlit);
		nreste -= nlit;
		pbuf += nlit;
	}
	return(noc-nreste);
}
/**/
/*****************************************************************/
/* Fonction pour la creation d'une adresse (service) pour la     */
/* Communication par socket                                      */
/*                                                               */
/* Entree : name : nom de la machine                              */
/*          port : numero de port pour le service                */
/* Sortie :                                                      */
/*         La fonction retourne (et alloue) un objet de type    */
/*                  struct sockaddr_in (internet adresse)       */
/*****************************************************************/
   

struct sockaddr_in *CreerSockAddr(char *name, int port) {
  struct sockaddr_in *adsock =(struct sockaddr_in *) 
    malloc(sizeof(struct sockaddr_in));

  struct hostent *haddr=NULL;
  struct in_addr **pptr;
  //char str[32];
#ifdef DEBUG
  printf("IN CreerSockAddr %s,%d\n", name, port);
#endif
  bzero(adsock, sizeof(struct sockaddr_in));
  if (name) {
    haddr = gethostbyname(name);
    if (haddr <= 0) {
      perror("Nom de machine inconnu");
    }
    else {
      pptr = (struct in_addr **) haddr->h_addr_list;
      memcpy(&adsock->sin_addr, *pptr, sizeof(struct in_addr));
      //inet_ntop(haddr->h_addrtype, *pptr, str, sizeof(str));
#ifdef DEBUG      
      printf("%s", str);
#endif
    }
  }
  else {
    adsock->sin_addr.s_addr=INADDR_ANY;
  }

  adsock->sin_family=AF_INET;
  adsock->sin_port = htons(port);
#ifdef DEBUG
  printf("fin\n");
#endif
    return (adsock);
}

/* ======================================================================
 * Creation d'une socket serveur UDP en l'associant au service definit 
 * Par numport                                                 
 * INPUT:
 *  IN nom : nom DNS de l'adresse
 *  IN numport : le numéro de port pour l'écoute UDP
 * ======================================================================
 */
	
int SockUdp(char *nom, int numport) {
  int sock;
  //int r=1;
  /* adsock : adresse de la socket d'écoute */
  struct sockaddr_in *adsock = (struct sockaddr_in *) 
    CreerSockAddr(nom, numport);

  if ((sock=socket(AF_INET,SOCK_DGRAM,0)) <= 0) {
    perror("\n pb creation socket \n");
  }
  /*	sock=dup(sock);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));
  */
#ifdef DEBUG
  printf("La socket num %d\n", sock);
#endif
  if (bind(sock,(struct sockaddr *) adsock, sizeof(*adsock)) <0) {
		perror("\n pb bind");
  }
  return(sock);
}

