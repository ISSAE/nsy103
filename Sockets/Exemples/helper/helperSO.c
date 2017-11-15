/**
 * Aide pour la création de socket et leur manipulation
 * Les étapes nécessaires
 * 1- créer socket
 * 2- créer adresse
 * 3- bind ou pas
 */
#include "helperSO.h"
/**
 * recuperer une information adresse addrinfo: 
 * cette adresse est prète pour socket et bind
 * Entree: 
 *  nom de host a chercher
 *  service : nom de service ou numéro de port ou null
 *  soktype : type de la socket  SOCK_STREAM ou SOCK_DGRAM
 * Sortie:
 *  adresse addrinfo
 * plus d'informations ici http://lps.cofares.net/Sockets/GetAddr/
 */
struct addrinfo *getAddrInfo(const char *nom, const char *service, int type) {
    struct addrinfo hints;
    struct addrinfo *result;
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

/**
 * 
 * @param sa : socket address
 * @return host:port
 */
char* getNameInfo(struct sockaddr_in *sa) {
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    char *resbuff;
    //printf("%d , %s\n",ntohs(sa->sin_port), inet_ntoa(sa->sin_addr));
    if (getnameinfo((struct sockaddr *)sa, sizeof(struct sockaddr_in), hbuf, sizeof (hbuf), sbuf,
            sizeof (sbuf), NI_NOFQDN | NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
        resbuff = malloc(NI_MAXHOST + NI_MAXSERV + 2);
        sprintf(resbuff, "ADDRESS %s:%s", hbuf, sbuf);
    }
    else {
        perror("getnameinfo");
        resbuff = NULL;
    }
    return resbuff;

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
 * Socket non bindé avec adresse IPV4 en résultat
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

int bindedSocket(char *nom, char* service, int type, struct sockaddr_in *addrin) {
    int sock = -1;
    int yes = 1;
    struct addrinfo *rp;
    rp = getAddrInfo(nom, service, type);


    if ((sock = socket(rp->ai_family, rp->ai_socktype,
            rp->ai_protocol)) <= 0) {
        perror("\n pb creation socket \n");
    }
    /* 
    SO_REUSEADDR is most commonly set in server programs.
    A common pattern is that you change a server configuration file and need to restart that server to make it reload its configuration. 
    Without SO_REUSEADDR, the bind() call in the restarted program's new instance will fail if there were connections open to the previous 
    instance when you killed it. 
    Those connections will hold the TCP port in the TIME_WAIT state for 30-120 seconds, so you fall into case 1 above.
    */
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
#ifdef DEBUG
    printf("La socket num %d\n", sock);
#endif
    if (bind(sock, rp->ai_addr, rp->ai_addrlen) < 0) {
        perror("\n pb de bind");
        sock = -2;
    }
    if (addrin !=NULL) {
         //On copie l'adresse
         memcpy(addrin, rp->ai_addr, rp->ai_addrlen);
    }
    freeaddrinfo(rp);
    return (sock);
}

