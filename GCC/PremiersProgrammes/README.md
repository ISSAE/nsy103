Processus de compilation generation de programme en Linux avec GCC (Gnu C Compiler)
====

* gcc -E : précompulation , nous utiliserons rarement
* gcc -S : compilation , nous utiliserons rarement
* gcc -c : assembleur , pour seulement compiler 
* gcc (ld) : edition de lien , pour générer l'exécutable

## Exemple d'utilisation

### un programme simple avec edition de lien par defaut

```bash
    $ gcc premierP.c
    $ gcc premierP.c 
    $ ls
    a.out  premierP.c  README.md
```
