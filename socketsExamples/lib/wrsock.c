/**
 * Ecriture sur une socket 
 * modification 2000/07/06 09:53:04 pfares Exp
 * Revision 1.2  1997/03/22  06:40:48  pascal
 * Revision 1.1  1997/03/22  06:26:10  pascal
 * Initial revision
 * 
 * Updated 9 janvier 2017 : utilisation de getaddrinfo
 */

#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/**
 * writes : Fonction pour l'ecriture en mode connecte sur un stream
 * INPUT:	                                                      
 *    IN sock : identifiant d'E/S fid                             
 *    IN pbuf : Le buffer utiliser pour l'écriture                
 *    IN noc : Le nobre d'actets à transmettre                    
 * OUTPUT                                                         
 *    OUT : Le nombre d'octets rééllement envoyés ou une erreur (<0)
 * Description:                                                   
 *    Dans certains cas la primitive système write n'envoie pas   
 *    tous les actets demandés (elle retourne le nombre d'octets  
 *    rééllement emis). On relance alors l'émisson jusqua épuisement 
 *    de tous les octets que l'on souhaite émettre                 
 * Alogirithme:                                                    
 *    tanque il reste des octets à emettre                         
 *        Emmetre les octets restants                              
 */

int writes(int sock, char *pbuf, int noc) {
    int nreste, //nombre d'octats restant à emmetre 
            necrit;
    //Variable qui contiendra le nb d'octets rééllement émis par write 
    //Initialement le nb d'octets restant a éméttre est noc 
    nreste = noc;
    while (nreste > 0) {
        necrit = write(sock, pbuf, nreste);
        //si necrit < 0 alors pb
        if (necrit < 0) return (necrit);
        nreste -= necrit;
        pbuf += necrit;
    }
    return (noc - nreste);
}

//*****************************************************************
//* Fonction pour la lecture en mode connecte                      
//*****************************************************************

int reads(int sock, char *pbuf, int noc) {
    int nreste, nlit;

    nreste = noc;
    while (nreste > 0) {
        nlit = read(sock, pbuf, nreste);
        if (nlit < 0) return (nlit);
        if (nlit == 0) return (noc - nreste);
        nreste -= nlit;
        pbuf += nlit;
    }
    return (noc - nreste);
}

/**
 * recuperer une information adresse addrinfo: 
 * cette adresse est prète pour socket et bind
 * Entree: 
 *  nom de host a chercher
 *  service : nom de service ou numéro de port ou null
 *  soktype : type de la socket  SOCK_STREAM ou SOCK_DGRAM
 * Sortie:
 *  adresse addrinfo
 */
struct addrinfo *getAddrInfo(const char *nom, const char *service, int type) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;
    memset(&hints, 0, sizeof (struct addrinfo));
    //hints.ai_family = AF_UNSPEC; * Allow IPv4 or IPv6 
    hints.ai_family = AF_INET; //Dans  notre cas seulement ipv4
    hints.ai_socktype = type;
    hints.ai_flags = AI_PASSIVE;
    //For wildcard IP address
    hints.ai_protocol = 0;
    //Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    s = getaddrinfo(nom, service, &hints, &result);
    if (s != 0) {
        perror("getaddrinfo");
        return NULL;
    }

    //revoyer l'information adresse  qui correspond
    return result;

}

/****************************************************************
 * Fonction pour la creation d'une adresse (service) pour la     
 * Communication par socket                                      
 *                                                               
 * Entree : name : nom de la machine                              
 *          port : numero de port pour le service                
 * Sortie :                                                      
 *         La fonction retourne (et alloue) un objet de type    
 *                  struct sockaddr_in (internet adresse)       
 */


struct sockaddr_in *creerSockAddr(char *name, char *port, int type) {
    //Création de la structure socketaddr : new
    struct addrinfo *res;
    res = getAddrInfo(name, port, type);

    return ((struct sockaddr_in *) res->ai_addr);
}

/**
 * Socket non bindé avec adresse en résultat
 *
 * Entree : name : nom de la machine
 * port : numero de port pour le service
 * type : socket
 * Sortie :
 * La fonction retourne(et alloue) un objet de type
 * struct sockaddr_in(internet adresse)
 * renvoie une socket dans socketId
 */

struct sockaddr_in *creerSock(char *name, char *port, int type, int *sockId) {
    //Création de la structure socketaddr : new
    struct addrinfo *res;
    res = getAddrInfo(name, port, type);
    if ((*sockId = socket(res->ai_family, res->ai_socktype,
            res->ai_protocol)) <= 0) {
        perror("\n pb creation socket \n");
    }
    //TODO copier avent de renvoyer et libérer res : freeaddrinfo(res); 
    return ((struct sockaddr_in *) res->ai_addr);
}

/**
 *Creation d'une socket en l'associant au service definit
 * Par nom : numport
 * INPUT :
 * IN nom : nom DNS de l'adresse
 * IN type : type(UDP = SOCK_DGRAM ou TCP = SOCK_STREAM)
 * IN numport : le numéro de port pour l'écoute UDP
 */

int bindedSocket(char *nom, char* service, int type) {
    int sock = -1;
    int yes=1;
    struct addrinfo *rp;
    rp = getAddrInfo(nom, service, type);


    if ((sock = socket(rp->ai_family, rp->ai_socktype,
            rp->ai_protocol)) <= 0) {
        perror("\n pb creation socket \n");
    }
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes);
#ifdef DEBUG
    printf("La socket num %d\n", sock);
#endif
    if (bind(sock, rp->ai_addr, rp->ai_addrlen) < 0) {
        perror("\n pb de bind");
        sock = -2;
    }
    freeaddrinfo(rp);
    return (sock);
}

