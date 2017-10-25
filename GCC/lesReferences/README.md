# Mémoire centrale et variables d'un programme

## La variable

Une variable possède un  nom (t), type (T), une valeur (v) et une adresse en mémoire adresseDeValeurDuNom

```C
    T t = v;
```

On pourrait la représenté sous la forme de (clé, valeurs) (n:T,v)  (nom:Type,valeur)


## L'ensemble des variables (environnement du programme ou du bloc)

L'environnement serait l'ensemble des variables (ie l'ensemble des clé/valeur)

Nous pouvons aussi considérer que l'adresse mémoire (référence) 
est aussi la clé de la variable
on retrouve la variable t de 2 manières a partir de son nom ou a partir de son adresse

(nom:Type, valeurDuNom) ou (adresseDeValeurDuNom, valeurDuNom)

en pseudo syntaxe C

(T n, v) (&n, v) ou &n indique l'adresse de la variable n.

n est une étiquette, &n est un nombre qui tous deux mêne a la même valeur (case mémoire)

## Une variable dont la valeur est une adresse

2:
```C
T *a = &n
```

ceci indique que la valeur de l'étiquette a est l'adresse de la variable n

(a:T, valeurDeA) d'après (2) valeurDeA est adresseDeValeurDeNom

## Syntaxxe en c

étiquette : (var, valeurDeVar)   
par référence : (&var, *(&var))

## Exemple en C avec les commentaires style clé valeur

3:
```C
int x=10; // [{x:10}] et supposons que l'adresse de x serait 1001 . cest a dire &x==1001
int *p;

p=&x; //sémantique de l'affectation : mettre dans p la valeur &x => [{p:1001},{x:10}] 

*p=20; //Mettre dans la mémoires référencé par p 20 => [{p:1001},{x:20}] remarque p nest pas modifié cest *p quí l'est (en quelques sorte *(&x)
```
## La zone mémoire d'unde déclaration C


Chaque zone possède 2 clés sont adresse et son nom (label) et une valeur dont la taille dépent du type

Ont pourrait par exemple modélisé ceci par 2 tableux 
```
MEM[adresse]=valeur //ceci représenterait la mémoire
ADRESSE[nom]=adresse //ceci représenterait la table de symbole geŕé par le compilateur
```

ont peut réaliser 2 opération de base sur les données en mémoire : lire et ecrire

```
lire(nom) : donne le résultat MEM[ADRESSE[NOM]]
ecrire(nom,valeur) : réalise MEM[ADRESSE[nom]]=valeur
```

### dans la syntaxe C de lexemple 3

int x=10;

Trouver une adresse pouvant contenir en int soit ADRESSEX cette adresse et y ecrire 10
MEM[ADRESSEX]=10 et ADRESSE[x]=ADRESSEX

int *p=&x;

Trouver une adresse pouvant contenir une référence de int (une adresse) soit ADRESSEP cette adresse et y ecrire &x
MEM[ADRESSEP]=ADRESSE[x] (cad ADRESSEX) et ADRESSE[p]=ADRESSEP

*p=20

MEM[MEM[ADRESSE[p]]]=20 cad MEM[MEM[ADRESSEP]]=20 cad MEM[ADRESSE[x]]=20 cad MEM[ADRESSEX]=20


