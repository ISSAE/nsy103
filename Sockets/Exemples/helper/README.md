#Librairie pour aider (faciliter) a créer et manipuler des sockets

## int writes(int, char *, int);

version writes, bouclant sur write pour essayer de tout transmettre

## int reads(int, char *, int);

version reads, blouclant sur read pour essayer de tout lire

## struct addrinfo *getAddrInfo(const char *, const char *, int);

Version simplifié de getaddinfo pour récupérer des adresse IPV4

## char* getNameInfo(struct sockaddr_in *sa);

version getnameinfo avec controle d'erreur

## struct sockaddr_in *creerSock(char *, char *, int, int *);

Créer une socket et une adresse socket sans bind

## int bindedSocket(char *, char *, int, struct sockaddr_in *);

Créer une socket bindée

## struct sockaddr_in *creerSockAddr(char *, char *, int);

Crée une adresse socket seule
