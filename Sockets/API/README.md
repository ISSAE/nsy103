# L'API Socket

* [socket()](#socket) Créer un point de communication
* [close()](#close) Fermer un descripteur de fichier mais aussi un socket
* [bind()](#bind) Fournir un nom ou une adresse à un socket
* [connect()](#connect) Débuter une connexion sur un socket
* [listen()](#listen) Attendre des connexions sur un socket
* [accept()](#accept) Accepter une connexion sur un socket
* [sendto()](#sendto) Envoyer un message sur un socket
* [recvfrom()](#recvfrom) Recevoir un message sur un socket
* [Comment remplir les adresses](../GetAddr/)

## Les primitives

Sous Linux, le Langage C nous fournit un certain nombre de primitives et structures pour manipuler les sockets.

En voici les principales

### socket

**Créer un point de communication**

```C
#include <sys/types.h> /* Consultez NOTES */
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

socket() crée un point de communication, et renvoie un **descripteur**.

Le  paramètre  **domain**  indique le domaine de communication pour le dialogue ; ceci sélectionne la famille de protocole à employer. Elles sont définies  dans le fichier <sys/socket.h>. Il existe plusieurs formats actuellement proposés. Nous n'utiliserons dans le cadre de ce tutoriel que :
`AF_INET  Protocoles Internet IPv4`

*si vous souhaitez connaitre les autres faire `man socket`*

Le socket a le type indiqué, ce qui indique la sémantique des communications. Plusieurs types sont définis actuellement. Nous n'utiliserons que :

<table>
<tr>
<td>SOCK_STREAM</td><td>Support  de dialogue garantissant l'intégrité, fournissant un flux de données binaires, et intégrant un mécanisme pour les transmissions de données hors-bande</td></tr>
<tr><td>SOCK_DGRAM</td><td>Transmissions  sans  connexion,  non garantie, de datagrammes de longueur maximale fixe.</td></tr>
</table>

Le **protocole** à utiliser sur le socket est indiqué par l'argument protocol.  Normalement, il n'y a qu'un seul protocole par type de socket pour une famille donnée, auquel cas l'argument protocol peut être nul.


### close 
**Fermer un descripteur de fichier mais aussi un socket**

```C
#include <unistd.h>

int close(int fd);
```
close()  ferme  le  descripteur  fd, de manière à ce qu'il ne référence plus aucun fichier, et puisse être réutilisé.


### bind 
**Fournir un nom à un socket**

```C
#include <sys/types.h>
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Quand  un socket est créé avec l'appel système socket, il existe dans l'espace des noms (famille  d'adresses et descripteur )  mais  n'a  pas  d'adresse réseaux assignée. bind() affecte l'adresse indiquée dans **addr** au socket référencé par le descripteur de fichier **sockfd**. addrlen indique la taille, en  octets, de la structure d'adresse pointée par addr cette taille est necessaire car les adresses peuvent êtres de plusieurs type et donc possiblement de taille différente. Traditionnellement cette opération est appelée *affectation d'un nom de service à une socket*.

La principale difficulté que rencontre un novice en C pour la création de socket est justement le remplissage de cette structure de donnée "__`struct sockaddr *addr`__". Nous verrons dans [Exemples simples](Exemples/) des solutions pour remplir cette struture en fonction du type et domaine de socket

La structure réellement passée dans le paramètre addr dépend du domaine de communication. La structure sockaddr est définie comme :

```C
struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
}
```

Le seul objet de cette structure est de transtyper  le  pointeur (cast) passé dans addr pour éviter les avertissements du compilateur. Voir [Exemples simples](Exemples/)

### connect
**Débuter une connexion sur un socket**

```C
#include <sys/types.h>
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
```
L'appel système connect() connecte le socket associé au descripteur de fichier sockfd  à  l'adresse  indiquée  par  addr.  L'argument  addrlen indique  la  taille  de addr. Le format de l'adresse addr est déterminé par la famille de la [socket sockfd](#socket)

### listen
**Débuter une connexion sur un socket**

```C
#include <sys/types.h> 
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

listen()  marque  le socket référencé par sockfd comme un socket passif, c'est-à-dire comme un socket qui sera utilisé pour accepter les demandes de connexions entrantes en utilisant [accept](#accept).

Le  paramètre sockfd est un descripteur de fichier qui fait référence à un socket de type SOCK_STREAM ou SOCK_SEQPACKET.

Le paramètre backlog définit une longueur maximale  pour  la  file  des connexions  en  attente  pour  sockfd. Si une nouvelle connexion arrive alors que la file est pleine, le client  reçoit  une  erreur  indiquant ECONNREFUSED

### accept
**Accepter une connexion sur un socket**

L'appel système accept() est employé avec les sockets utilisant un protocole en mode connecté (SOCK_STREAM).  Il  extrait  la première  connexion  de  la file des connexions en attente du socket sockfd à l'écoute, cré un nouveau socket et alloue pour ce socket un  **nouveau  descripteur**  de  fichier qu'il renvoie. Le nouveau socket n'est pas en état d'écoute. Le socket original sockfd n'est pas modifié par l'appel système.

L'argument  sockfd  est  un  socket  qui  a été créé avec la fonction [socket](#socket),  attaché  à  une  adresse  avec  [bind](#bind),  et  attend   des connexions après un appel [listen](#listen).

### sendto
**Envoyer un message sur un socket**

```C
#include <sys/types.h>
#include <sys/socket.h>

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
```

Les appels système sendto() permettent de transmettre un message depuis le socket source sockfd à destination d'un autre socket référencé par son adresse dest_addr. Le message se trouve dans buf et a pour longueur len

### recvfrom
**Recevoir un message sur un socket**
 
 Les  appels  système recvfrom() et sont utilisés pour recevoir des messages depuis un socket, et peuvent servir sur un socket orienté connexion ou non. recvfrom() enregistre le message reçu dans le tampon buf. Le processus appelant doit préciser la taille de ce tampon dans len. Si src_addr n'est pas NULL, et si le protocole sous-jacent fournit l'adresse de la source, celle-ci y est insérée dans le tampon désigné par src_addr. Dans ce cas, addrlen est  un paramètre-résultat.

 Si le processus appelant n'est pas intéressé par l'adresse de la source, src_addr doit avoir la valeur NULL, et addrlen doit valoir 0.




[Linux programmation système (Index)](http://lps.cofares.net/)
