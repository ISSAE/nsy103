#Mémoire centrale et variables d'un programme

##La variable

Une variable possède un  nom (n), type (T) et une valeur (v)

```C
    T t = v;
```

On pourrait la représenté sous la forme de (clé, valeurs) (n:T,v)  (nom:Type,valeur)


##L'ensemble des variables (environnement du programme ou du bloc)

L'environnement serait l'ensemble des variables (ie l'ensemble des clé/valeur)

Nous pouvons aussi considérer que l'adresse mémoire (référence) 
est aussi la clé de la variable
on retrouve la variable n de 2 manières a partir de son nom ou a partir de son adresse

(nom:Type, valeurDeNom) ou (adresseDeValeurDeNom, valeurDeNom)

en syntaxe C

(T n, v) (&n, v) ou &n indique l'adresse de la variable n.

n est une étiquette, &n est un nombre qui tous deux mêne a la même valeur (case mémoire)

##Une variable dont la valeur est une adresse

2:
```C
T *a = &n
```

ceci indique que la valeur de l'étiquette a est l'adresse de la variable n

(a:T, valeurDeA) d'après (2) valeurDeA est adresseDeValeurDeNom

##Syntaxxe en c

étiquette : (var, valeurDeVar)   
par référence : (&var, *(&var))



