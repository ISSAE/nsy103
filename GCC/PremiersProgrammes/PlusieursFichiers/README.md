
## Exemple d'utilisation

### un programme simple avec edition de lien

> Pour compiler et générer un executable
>
> gcc -c <Vos programme.c>
>   
> gcc -c main.c
>   
> gcc -c f.c
>   
> gcc -o pgm main.o f.o
>   
> TODO : Nous verrons plus tard comment créer des librairies (statique et dynamique)
>
 
### premiere compilation

```bash
$ gcc -c main.c 
main.c: In function ‘main’:
main.c:16:27: warning: implicit declaration of function ‘f’ [-Wimplicit-function-declaration]
    printf("f(%d)=%d\n",10,f(10));
                           ^
```
Pourqoui cette alerte

1. Le compilateur ne sachant pas quel est le type de retout de f il nous indique qu'il va considérer ceci comme implicite (c'est à dire int)

2. pour clarifier les choses nous devons indiquer au compilateur quel est la signature de f (juste une declaration) `int f();` aisi le compilateur saura que la fonction f retourne un entier. Au moment de la compilation le compilateur n'a pas besoin de l'implémentation de la fonction f (le code). cest au moment de l'edition de lien que l'implémentation est necessaire.

nous aurons le choix soit dajouter la signature dans le fichier main.c (avant l'utilisation de la fonction) soit de mettre les sigtnatures dans un fichier de signature (header) qui sont les .h et faire un #include





