# Communication entre processus en réseaux : les Sockets

## L'API 

* [Les primitives de l'API Socket](API/) et les studtures de données utilisés
* [Exemples simples](Exemples/)
* [Comment remplir la structure représentant des adresses](GetAddr/)

## Généralités

Un socket représente une prise par laquelle une application peut envoyer et recevoir des données. Cette prise permet à l'application de se brancher sur un réseau et communiquer avec d'autres applications qui y sont branchées. Les informations écrites sur une prise depuis une machine sont lues sur la prise d'une autre machine, et inversement. Il existe différents modèles de prises, en fonction des protocoles réseau; le plus fréquent sont les socket TCP/IP.C'est un des premiers produits **open source** de l'histoire

La fonction socket de cette API sert à créer un certain type de prise. Le type de prise sera choisi en fonction de la technologie de communication à utiliser (par exemple TCP/IP). L'API permet à un logiciel serveur de servir plusieurs clients simultanément. Sur les systèmes d'exploitation Linux le programme serveur pourra utiliser la fonction fork ou la création de thread pour chaque demande d'un client.

### mode connecté

Le mode connecté (comparable à une communication téléphonique), utilisant le protocole TCP. Dans ce mode de communication, une connexion durable est établie entre les deux processus, de telle façon que l’adresse de destination n’est pas nécessaire à chaque envoi de données.

Une connexion est établie entre le client et le serveur en vue de permettre la communication. La fonction **connect** permet à un client de demander la connexion à un serveur, et la fonction **accept** permet à un serveur d'accepter cette connexion. Le programme serveur utilisera préalablement la fonction **listen** pour informer le logiciel sous-jacent qu'il est prêt à recevoir des connexions. Une fonction **close** permet de terminer la connexion. Lorsqu'un des deux interlocuteurs termine la connexion, l'autre est immédiatement avisé.

Une fois la connexion établie, les fonctions standard du SGF, **write** et **read** servent respectivement à envoyer et à recevoir des informations. 

Des fonctions auxiliaires **gethostbyname** et **getaddrinfo** permettent d'obtenir l'adresse IP d'une machine en interrogeant le DNS, adresse qui sera utilisée par d'autres fonctions de l'API.

### mode datagram

Le mode non connecté (analogue à une communication par courrier), utilisant le protocole UDP. Ce mode nécessite l’adresse de destination à chaque envoi, et aucun accusé de réception n’est donné.

En mode non connecté il n'y a pas de connection établit la socket est directement utilisé, les fonctions send et recv servent respectivement à envoyer et à recevoir des informations.

### type de socket

Chaque socket possède un type et un ou plusieurs processus qui lui sont associés. Il est également caractérisé par le domaine de communication dans lequel il se trouve. Ce dernier est une abstraction qui permet de regrouper les processus ayant des propriétés communes et communiquant par l'intermédiaire de sockets. Normalement, un socket ne peut échanger des données qu'avec un socket se trouvant dans le même domaine de communication.

La communication inter-processus de supporte deux domaines de communication :

* le domaine Unix dans lequel deux processus se trouvant sur la même station Unix uniquement peuvent communiquer6 ;
* le domaine Internet pour les processus utilisant le protocole TCP/IP pour communiquer entre eux.
