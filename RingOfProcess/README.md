#﻿TP conclusion NSY103 Linux : programmation système




Nous souhaitons réaliser une communication entre processu (ou services) basée sur une séquence  (anneau) de processus <p1,..,pi,...,pn>. Les processus auront à communiquer entre eux avec la contrainte qu'un processus i ne reçoit (lit) des informations que de son prédécesseur et ne transmet de l'information qu'à son successeur. Le successeur de pn étant p1, et ainsi nous créons un anneau. 
Cette organisation permet à tout processus pi de communiquer avec un processu pj en transmettant le message vers son successeur jusqu'à arriver à la destination. l'avantage d'une telle organisation c'est qu'un processus pi n'a pas à connaître toutes les adresses de tous les autres processus, mais seulement l'adresse de son successeur


  Ainsi chaque processus ou service aura un seul point d'entrée (lecture) et un seul point de sortie (ecriture)


##I) Conteur circulant 
En se basant sur une telle organisation il vous est demandé de réaliser un anneaux ou chaque processus aura à incrémenter la valeur d'un compteur lue et la transmet à son successeur. La circulation du compteur pourra s'arrêter par exemple quand on atteindra une certaine valeur LIMITECONTEUR.


###I.1 : Réalisation du service Pi, que nous nommerons "inc", indépendant de l'environnement. 
Réaliser un processus Linux qui lit son entrée standard, incrémente la valeur, puis la transmet à sa sortie standard.


###I.2 : enchainer 2 inc
Réaliser un processus "chef" qui créera 2 fils, chaque fils lancera (par recouvrement) inc de telle sorte que la sortie du premier inc soit l'entrée du second
  
```
 #include <unistd.h>
       int dup(int oldfd);
       int dup2(int oldfd, int newfd);
       #define _GNU_SOURCE             /* Consultez feature_test_macros(7) */
       #include <fcntl.h>      /* Définitions des constantes O_*   */
       #include <unistd.h>
       int dup3(int oldfd, int newfd, int flags);
DESCRIPTION
       Ces appels système créent une copie du descripteur de fichier oldfd.
       dup()  utilise  le plus petit numéro inutilisé pour le nouveau descrip‐
       teur.
       dup2() transforme newfd en une copie de oldfd, fermant auparavant newfd
       si besoin est.
```

1. utiliser pour réaliser ceci fork, une primitive de la famille exec et dup ou dup2
2. Pourquoi utiliser dup ou dup2?

###I.3 création de l'anneau de 2 processus

1. maintenant modifier le "chef" précédent de telle sorte que la sortie de fils2 devient l'entŕre de fils1 
2. Que se passe-t-il si vous lancez ce système?
3. Proposer une solution pour initier le traitement dans la boucle

###I.4 On généralise a l'anneaux de n processus (service)

##II Les processus sont maintenant des services sur le réseaux (chaque processus peut être sur une machine différente)
II.1 modifier inc
Créer un service  "Sinc" pour qu'il reçoive l'information sur une socket d'entrée et la transmet vers la socket de sortie (qui correspond au successeur) l'opération réalisée est délégué à "inc", 


Questions que vous pourriez vous poser
1. quelles sont les informations nécessaires? 
2. Quand "inc" va créer la socket d'entrée à qui doit-il transmettre les informations permettant la connection à cette socket?
3. Comment peut-il récupérer l'information de son successeur?


II.2
[Linux programmation système (Index)](http://lps.cofares.net/)
