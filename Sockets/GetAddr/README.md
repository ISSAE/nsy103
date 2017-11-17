# Traduction d'adresses et de services réseau

Étant  donnés  node  et  service,  qui  identifient  un hôte Internet et un service, getaddrinfo() renvoie une ou plusieurs structure addrinfo, chacune d'entre elles contenant une adresse Internet qui puisse être indiquée dans un appel à [bind](../Api/#bind) ou [connect](../APi/#connect). La fonction getaddrinfo() combine la fonctionnalité fournie par les fonctions gethostbyname  et getservbyname en une interface unique, mais à l'inverse de ces fonctions, getaddrinfo() est réentrante et permet aux programmes d'éliminer la dépendance envers IPv4 ou IPv6.

La structure addrinfo utilisée par getaddrinfo() contient les membres suivants :

```C
           struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };
```

Le  paramètre  hints pointe sur une structure addrinfo qui indique les critères de sélection des structures d'adresses de sockets renvoyées dans la liste pointée par res. Si hints n'est pas NULL, il doit pointer sur une structure addrinfo dont les membres ai_family, ai_socktype, et ai_protocol indiquent les critères limitant l'ensemble d'adresses de sockets renvoyées par getaddrinfo(), de la façon suivante :

* **ai_family**   Ce  champ  indique la famille d'adresse désirée des adresses renvoyées. AF_INET et AF_INET6 font partie des valeurs valables pour ce champ. La valeur AF_UNSPEC indique que getaddrinfo() doit renvoyer les adresses de socket de n'importe quelle famille d'adresses (par exemple, IPv4 ou IPv6) pouvant être utilisées avec node et service.

* **ai_socktype** Ce champ indique le type préféré de socket, par exemple SOCK_STREAM ou SOCK_DGRAM. Mettre 0 dans ce champ indique que getaddrinfo() peut renvoyer n'importe  quel  type d'adresse de socket.

* **ai_protocol** Ce champ indique le protocole des adresses de socket renvoyées. Mettre 0 dans ce champ indique que getaddrinfo() peut renvoyer des adresses de socket de n'importe quel type.

* **ai_flags**    Ce champ indique des options supplémentaires, décrites ci-dessous. Plusieurs attributs peuvent être indiqués en les groupant par un OU binaire.

>>> **IMPORTANT** Tous les autres membres de la structure pointée par hints doivent contenir 0 ou être des pointeurs NULL.

Spécifier hints à NULL est équivalent à définir ai_socktype et ai_protocol à 0, ai_family à AF_UNSPEC et ai_flags à (AI_V4MAPPED | AI_ADDRCONFIG). (POSIX spécifie d'autres valeurs
par  défaut  pour  ai_flags ;  consultez les NOTES.) node indique soit une adresse réseau en format numérique (décimal pointé pour l'IPv4, comme prise en charge par inet_aton hexadécimal pour l'IPv6, comme prise en charge par inet_pton(3)), soit un nom d'hôte, dont l'adresse réseau est alors résolue. Si  le  membre  hints.ai_flags  contient  l'attribut AI_NUMERICHOST alors node devra être une adresse réseau numérique. L'attribut AI_NUMERICHOST empêche toute tentative, éventuellement longue, de résolution de nom d'hôte.

Si  l'attribut  AI_PASSIVE  est  indiqué dans hints.ai_flags, et si node est NULL, les adresses de socket renvoyées seront pertinentes pour lier (bind(2)) une socket qui acceptera [accept](../API/#accept) les connexions. Les adresses de socket renvoyées contiendront l'« adresse joker » (wildcard adress) (INADDR_ANY pour  les  adresses  IPv4,  IN6ADDR_ANY_INIT  pour  les adresses  IPv6).  L'« adresse  joker »  est  utilisée par des applications (typiquement des serveurs) qui ont l'intention d'accepter des connexions de n'importe quel hôte. Si node  n'est pas NULL, l'attribut AI_PASSIVE est ignoré.

Si l'attribut AI_PASSIVE n'est pas positionné dans hints.ai_flags, les adresses de  socket  renvoyées  seront pertinentes  pour  être  utilisées  avec  [connect](../API/#connect),  sendto.  Si node est NULL, l'adresse réseau sera définie avec l'adresse de l'interface de boucle (loopback) (INADDR_LOOPBACK pour les adresses IPv4, IN6ADDR_LOOPBACK_INIT pour les adresses IPv6) ; cela est utilisé par les applications qui doivent communiquer avec des correspondants s'exécutant sur la même machine.

**service** définit le port dans chacune des structures d'adresses renvoyées. Si cet argument est un nom de service, il est convertit en  son  numéro  de  port correspondant.  Cet argument peut également être indiqué sous forme décimale, qui est simplement converti en binaire. Si service est NULL, le numéro de port des adresses de socket renvoyées n'est pas initialisé. Si AI_NUMERICSERV est indiqué dans hints.ai_flags et si service n'est pas NULL, service doit pointer vers une chaîne contenant une valeur numérique de port. Cet attribut est utilisé pour inhiber l'invocation du service de résolution des noms dans les cas où l'on sait qu'il n'est pas nécessaire. node ou service peuvent être NULL, mais pas les deux à la fois.


## Exemple de helper (fonction simplifiant l'utilisation d'une autre fonction) permettant de s'implifié l'utilisation de getaddrinfo et sá daptant bien a nos besoin dans les exemples de ce projet

cette fonction permet de recuperer une information adresse de type struct addrinfo. Cette adresse est prète pour socket et bind

Entree: 
*  nom de host a chercher
*  service : nom de service ou numéro de port ou null
*  soktype : type de la socket  SOCK_STREAM ou SOCK_DGRAM
Sortie:
*  adresse addrinfo

```C
struct addrinfo *getAddrInfo(const char *nom, const char *service, int type) {
    struct addrinfo hints;
    struct addrinfo *result;
    int s;
    memset(&hints, 0, sizeof (struct addrinfo));
    //hints.ai_family = AF_UNSPEC; * trouver IPv4 ou IPv6 
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
```