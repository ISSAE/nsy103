# Processu Linux

* [Création de pocessu : fork](#fork)

# fork 
- Créer un processus fils

```C
       #include <unistd.h>

       pid_t fork(void);
```

## DESCRIPTION

fork()  crée  un nouveau processus en copiant le processus appelant. Le nouveau processus, qu'on appelle fils (« child »), est une copie exacte du  processus  appelant,  qu'on appelle père ou parent, avec les exceptions suivantes :

* Le fils a son propre identifiant de processus unique.
* L'identifiant de processus parent (PPID) du fils  est  l'identifiant de processus (PID) du père.
