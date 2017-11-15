# L'API Socket

## Les primitives

Sous Linux, le Langage C nous fournit un certain nombre de primitives et structures pour manipuler les sockets.

En voici les principales

### socket - Créer un point de communication

```C
#include <sys/types.h> /* Consultez NOTES */
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

socket() crée un point de communication, et renvoie un **descripteur**.

Le  paramètre  **domain**  indique le domaine de communication pour le dialogue ; ceci sélectionne la famille de protocole à employer. Elles sont définies  dans le fichier <sys/socket.h>. Il existe plusieurs formats actuellement proposés nous n'utiliserons dans le codre de ce tutoriel que:
`AF_INET  Protocoles Internet IPv4`

*si vous souhaitez connaitre les autre faire `man socket`*

La socket a le type indiqué, ce qui indique la sémantique des  communcations. Plusieurs types sont définis actuellement nous n'utiliserons que :

| | |
|-|-|-|
| SOCK_STREAM  |   Support  de dialogue garantissant l'intégrité,     fournissant un flux de données binaires, et intégrant un mécanisme pour les transmissions de données hors-bande |
|SOCK_DGRAM|Transmissions  sans  connexion,  non garantie, de datagrammes de longueur maximale fixe.|
Le **protocole** à utiliser sur la socket est indiqué par l'argument protocol.  Normalement, il n'y a qu'un seul protocole par type de socket pour une famille donnée, auquel cas l'argument protocol peut être nul.


### close - Fermet un descripteur de fichier mais aussi un socket

```C
#include <unistd.h>

int close(int fd);
```
close()  ferme  le  descripteur  fd, de manière à ce qu'il ne référence plus aucun fichier, et puisse être réutilisé.


### bind - Fournir un nom à une socket

```C
#include <sys/types.h>
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Quand  un socket est créée avec l'appel système socket, elle existe dans l'espace des noms (famille  d'adresses et descripteur)  mais  n'a  pas  d'adresse réseaux assignée. bind() affecte l'adresse indiquée dans **addr** à la socket référencée par le descripteur de fichier **sockfd**. addrlen indique la taille, en  octets, de la structure d'adresse pointée par addr cette taille est necessaire car les adresses peuvent êtres de plusieurs type et donc possiblement de taille différente. Traditionnellement cette opération est appelée *affectation d'un nom de service à une socket*.

La principale difficulté que rencotre un novice en C pour la création de socket est justement le remplissage de cette structure de donnée "__`struct sockaddr *addr`__". Nous verrons dans [Exemples simples](Exemples/) des solution pour remplire cette struture en fonction du type et domaine de socket

La structure réellement passée dans le paramètre addr dépend du domaine
       de communication. La structure sockaddr est définie comme :
```C
struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
}
```

Le seul objet de cette structure est de transtyper  le  pointeur (cast) passé dans addr pour éviter les avertissements du compilateur. Voir [Exemples simples](Exemples/)

