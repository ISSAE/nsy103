# SGF (présentation rapide)
Un système de gestion de fichiers (SGF) est l'ensemble des primitives permettant de stocker les informations et de les organiser dans des fichiers sur ce que l'on appelle des mémoires secondaires ou encore des supports de persistance.

## Un fichier

Un fichier informatique est une collection un ensemble de données numériques réunies sous un même nom, enregistrées sur un support de stockage permanent (persistant).

Pour Linux, les fichiers sont organisés dans des fichiers particulier dit répertoires (directory), afin de faciliter leur référencement (donner un nom à une entité fichier)

## Les couches logiciel SGF Linux

![Couche logiciel SGF](/imgs/CoucheSGF.png)

## Les concepts:
* Fichier
* Enregistrement

* Les concepts logiques ont pour but:
  * de ranger de manière rationnelle les données sur disque 
  * de rendre transparents à l'utilisateur les concepts physiques
  * de gérer les fichiers indépendamment des périphériques

* Les concepts logiques sont gérés par le SGF
  > Le SGF s'appuie sur la gestion des concepts physiques

## API SGF Linux 
>>> *Un simple survol* 

![Principe SGF Linux](/imgs/SGFLinuxPrinceipes.png)

L'interface logiciel est composé d'un [ensemble de primitives](APISGF.md) en voici l'essentiel ([suivre le lien](APISGF.md))

# Généralités descripteur de fichier

Un descripteur de fichier est une clé abstraite (au niveaux d'un processus) pour accéder à un fichier (c'est un entier).

Un descripteur de fichier est un index d'une entrée dans le noyau-système, une structure de données contenant les détails de tous les fichiers ouverts.

Dans Linux, on appelle cette structure de données une table de descripteurs de fichier. Et chaque processus a sa propre table de descripteurs de fichier. L'application utilisateur passe la clé abstraite au noyau par un appel système et le noyau accédera au fichier grâce à cette clé. L'application ne peut pas lire ou écrire directement la table des descripteurs de fichier.

Les descripteurs de fichier peuvent désigner des fichiers, des répertoires, des devices bloc ou caractère (souvent appelés fichiers spéciaux), des pipes nommés ou des pipes anonymes, des sockets.

![Descripteur de fichier](/imgs/fd.gif "File Descriptor tables")