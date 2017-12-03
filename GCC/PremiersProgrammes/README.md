Processus de compilation generation de programme en Linux avec GCC (Gnu C Compiler)
====

* gcc -E : précompulation , nous utiliserons rarement
* gcc -S : compilation , nous utiliserons rarement
* gcc -c : assembleur , pour seulement compiler 
* gcc (ld) : edition de lien , pour générer l'exécutable

## Exemple d'utilisation

### un programme simple avec edition de lien par defaut


> Pour compiler et générer un executable
>
> gcc -o <nomdevotrechoix> <Votre programme.c>
>   
> dans notre cas
>
> gcc -o pgm1 premierP.c
>
> si vous omettez -o gcc génère l'executable a.out

```bash
    $ gcc premierP.c
    $ gcc premierP.c 
    $ ls
    a.out  premierP.c  README.md
```
[Linux programmation système (Index)](http://lps.cofares.net/)
