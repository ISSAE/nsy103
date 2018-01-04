[Index Home](/) | [<- Base Programmation Linux](..) 
-----------------|-------------------------------

# Exemple tube Linux (pipe)

```C
#include <unistd.h>
int pipe(int pipefd[2]);
```

 pipe()  crée un tube, un canal unidirectionnel de données qui peut être utilisé pour la communication entre processus. Le  tableau  pipefd  est utilisé  pour  renvoyer  deux descripteurs de fichier faisant référence aux extrémités du tube. pipefd[0] fait référence à l'extrémité de  lecture  du  tube.  pipefd[1]  fait  référence à l'extrémité d'écriture du tube. Les données écrites sur l'extrémité d'écriture du tube sont mises en  mémoire  tampon  par  le  noyau jusqu'à ce qu'elles soient lues sur l'extrémité de  lecture du tube.

 ```C
#include <unistd.h>
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```
Ces appels système créent une copie du descripteur de fichier oldfd.

dup()  utilise  le plus petit numéro inutilisé pour le nouveau descripteur.

dup2() transforme newfd en une copie de oldfd, fermant auparavant newfd si besoin, sauf exceptions :

*  Si  oldfd n'est pas un descripteur de fichier valable, alors l'appel échoue et newfd n'est pas fermé.
*  Si oldfd est un descripteur de fichier valable et newfd  a  la  même valeur que oldfd, alors dup2() ne fait rien et renvoie newfd.


[Linux programmation système (Index)](http://lps.cofares.net/)
