# Les References Fonctions

## Pointeurs et références de fonctions


Il est possible de faire des pointeurs de fonctions. Un pointeur de fonction contient l'adresse du début du code binaire constituant la fonction. Il est possible d'appeler une fonction dont l'adresse est contenue dans un pointeur de fonction avec l'opérateur d'indirection *.

Pour déclarer un pointeur de fonction, il suffit de considérer les fonctions comme des variables. Leur déclaration est identique à celle des tableaux, en remplaçant les crochets par des parenthèses :

type (*identificateur)(paramètres);
où type est le type de la valeur renvoyée par la fonction, identificateur est le nom du pointeur de la fonction et paramètres est la liste des types des variables que la fonction attend comme paramètres, séparés par des virgules.

### Exemple Déclaration de pointeur de fonction
```C
int (*pf)(int, int);   /* Déclare un pointeur de fonction. */
```
pf est un pointeur de fonction attendant comme paramètres deux entiers et renvoyant un entier.

Il est possible d'utiliser typedef pour créer un alias du type pointeur de fonction :

Par eexemple

``` C
typedef int (*PFonc)(int, int);
PtrFonct pf;
```

`PtrFonct` est le type des pointeurs de fonctions.

Si f est une fonction répondant à ces critères, on peut alors initialiser pf avec l'adresse de f. De même, on peut appeler la fonction pointée par pf avec l'opérateur d'indirection.

### Un exemple de déréférencement de pointeur de fonction

```C
#include <stdio.h>    /* Entrées sorties standard */

/**
 * Fonction f renvoie la somme des 2 paramètres en entrées
 */
int f(int i, int j)
    return i+j;
}

int (*pf)(int, int);  /* Déclare un pointeur de fonction. */

int main(void)
{
    int l, m;         /* Déclare deux entiers. */
    pf = &f;          /* Initialise pf avec l'adresse de la fonction f. */
    printf("Entrez le premier entier : ");
    scanf("%u",&l);   /* Initialise les deux entiers. */
    printf("\nEntrez le deuxième entier : ");
    scanf("%u",&m);

/* Utilise le pointeur pf pour appeler la fonction f
   et affiche le résultat : */

    printf("\nLeur somme est de : %u\n", (*pf)(l,m));
    return 0;
}
```
L'intérêt des pointeurs de fonction est de permettre l'appel d'une fonction parmi un éventail de fonctions au choix.

Par exemple, il est possible de faire un tableau de pointeurs de fonctions et d'appeler la fonction dont on connaît l'indice de son pointeur dans le tableau. Afin de permettre un program,mation dynamique.

Ou aussi dan sles cas ou nous avon sbesoin de fournir a un service une traitement a réalisé tel que c'est le cas pour les [signaux](/BaseProgLinux/Signals) et les [thread](/BaseProgLinux/Threads)

### Une autre application des pointeurs de fonctions

```C
#include <stdio.h>  /* Autorise l'emploi de scanf et de printf. */

/* Définit plusieurs fonctions travaillant sur des entiers : */

int somme(int i, int j)
{
    return i+j;
}

int multiplication(int i, int j)
{
    return i*j;
}

int quotient(int i, int j)
{
    return i/j;
}

int modulo(int i, int j)
{
    return i%j;
}

typedef int (*fptr)(int, int);
fptr ftab[4];

int main(void)
{
    int i,j,n;
    ftab[0]=&somme;          /* Initialise le tableau de pointeur */
    ftab[1]=&multiplication; /* de fonctions. */
    ftab[2]=&quotient;
    ftab[3]=&modulo;
    printf("Entrez le premier entier : ");
    scanf("%u",&i);          /* Demande les deux entiers i et j. */
    printf("\nEntrez le deuxième entier : ");
    scanf("%u",&j);
    printf("\nEntrez la fonction : ");
    scanf("%u",&n);          /* Demande la fonction à appeler. */
    if (n < 4)
        printf("\nRésultat : %u.\n", (*(ftab[n]))(i,j) );
    else
        printf("\nMauvais numéro de fonction.\n");
    return 0;
}
```


