# Les étapes pour la communication socket (Les protocoles TCP et UDP)

Vous trouverez le premier exemple simple en TCP [Exemple echo client server TCP](EchoTCP) et en UDP [Exemple echo client server UDP](EchoUDP)

## mode connecté TCP

![TCP](Socket-Workflow.png)

### Le client

1. Création d'un socket avec la primitive [socket()](../API/#socket)
2. Connexion au serveur
   1. Récupération et initialisation de l'adresse du serveur (gethostbyname ou getaddrinfo) J'utiliserais [getaddrinfo()](../GetAddr)
   2. Connexion primitive [connect()](../API/#connect)
3. (répétition) Envoi et réception de données (read et write) entre le client et le serveur (un socket est un file descriptor)
4. Fermeture du socket avec la primitive close 

### Le serveur

1. Création d'un socket primitive [socket()](../API/#socket)
2. Création du socket d'écoute
   1. Initialisation d'une adresse ip:port (interface) dans la structure sockaddr_in pour le socket d'écoute en initialisant une structure d'adresse. Ceci peut être fait directement ou en utilisant l'une des primitives (gethostbyname ou getaddrinfo) voir [Exemples](../Exemples)
   2. Association de l'adresse au socket avec la primitive [bind()](#bind)
3. Mise en attente des connexions avec la primitive [listen()](../API/#listen)
4. Acceptation de la connexion avec la primitive [accept()](../API/#accept)
5.  (répétition) Envoi et réception de données (read et write) entre le client et le serveur (un socket est un file descriptor)
6. Fermeture du socket avec la primitive close 

## Le mode non connecté UDP

![UDP](conn_less.gif)
### Le client

1. Création d'un socket avec la primitive [socket()](../API/#socket)
2. Recupération et initialisation de l'adresse du serveur (gethostbyname ou getaddrinfo) J'utiliserais [getaddrinfo()](../GetAddr)
3.  (répétition) Envoi et reception de données [sendto()](API/#sendto) et [recvfrom()](API/#recvfrom)
4. Fermeture du socket

### Le serveur

1. Création d'un socket avec la primitive [socket()](../API/#socket)
2. Création de l'interface (le service):  un ip port pour les clients
   1. Initialisation d'une adresse ip:port (interface) dans la structure sockaddr_in pour le socket d'écoute en initialisant une structure d'adresse pouvant être attribuée directement ou en utilisant l'une des primitives (gethostbyname ou getaddrinfo) voir [Exemples](../Exemples)
   2. Association de l'adresse au socket avec la primitive [bind()](#bind)
3.  (répétition) Envoi et réception de données [sendto()](API/#sendto) et [recvfrom()](API/#recvfrom)
4. Fermeture du socket[Linux programmation système (Index)](http://lps.cofares.net/)
