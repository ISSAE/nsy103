[Index Home](/) |
----

# Le problème due a la concurrence (parallélisme d'exécution)

## Entrelacement non déterministe

Soit les 2 processus suivant
<table><tr>
    <th>P1</th>
    <th>P2</th> 
</tr>
<tr><td><code><pre>
while(1) {
    I1.1 
    I1.2 
}
</pre></code></td><td><code><pre>
while(1) {
    I2.1 
    I2.2 
}
</pre></code></td></tr>
</table>

Les exécutions possible sont:

1. I1.1 I1.2 I2.1 I2.2
2. I1.1 I2.1 I1.2 I2.2
3. I1.1 I2.1 I2.2 I1.2
4. I2.1 I1.1 I2.2 I1.2
4. I2.1 I1.1 I1.2 I2.2
5. I2.1 I2.2 I1.1 I1.2

Pour que cette application soit valide, il faut que toutes les séquences possibles donnent le même résultat pour les même conditions préalable. La validité du résultat ne peut pas être garantie si ces instructions manipulaient des données communes aux deux processus.

Prenons le cas `x=x+1;` cette instruction se décompose en trois instructions élémentaires (au niveaux du langage machine)

1. **R <- (x)** : mettre dans un register la valeur de x
2. **R+1** : Incrémenter le registre de la valeur 1 (c'est une seule instruction  en principe)
3. **(x) <- R** : déposer dans x la valeur contenu dans R

Nous aurons donc un entrelacement entres ces 3 instructions en cas de parallélisme

ainsi si `x == 0`
après l'exécution concurrente de x=x+1 dans 2 processus.
x=x+1 | x=x+1
---|---
Le résultat est 1 ou 2. Ceci n'arriverait pas si l'instruction x=x+1 était atomique

Voir cet exemple [Concurence](/BaseProgLinux/Threads/concurence.c)

# Quels solutions alors dans Linux?

## Exclusion mutuelle
L'exclusion mutuelle est le mécanisme qui permet qu'une et une seule tâche accède à une ressource partagée à la fois à un instant donné. Pour cela, on utilise une variable spéciale appelée sémaphore d'exclusion mutuelle qui joue le rôle de verrou pour accéder à la ressource. Sous Posix, elle est mise en place via les 3 primitives suivants :

1. La déclaration `pthread_mutex_t verrou`
3. La primitive  d'initialisation `pthread_mutex_init(pthread_mutex_t *verrou, const pthread_mutextattr_t *m_attr)`
4. La primitive permettant à une tâche de prendre le verrou  `pthread_mutex_lock(pthread_mutex_t *verrou)`
5. La primitive permettant à une tâche de libérer le verrou après avoir utilisé la donnée partagée :`pthread_mutex_unlock(pthread_mutex_t *verrou)`

## Sémaphore

## Sémaphore POSIX

Voir [Les sémaphore POSIX](/BaseProgLinux/Threads/SemaphoreTh.md)

## Sémaphore System V

Voir [Les sémaphores, concept et implémentation](/ProgAvancee/SemaphorePourProc/semaphor.md)

## Des problèmes résolues avec des sémaphores

### Exclusion mutuelle
### Rendez-vous
### Producteurs consommateurs 
### Lecteurs rédacteurs

voir [Solutions problèmes classiques avec Sémaphores](/ConcurenceEtSynchro/SolutionsProblesConcurence.md)

## Variable condition

Une  condition  (abréviation  pour "variable condition") est un mécanisme de synchronisation permettant à un thread de suspendre son exécution jusqu'à ce qu'une certaine condition (un prédicat) sur des données partagées soit vérifiée. Les opérations fondamentales  sur  les  conditions  sont : signaler la condition (quand le prédicat devient vrai) et attendre la condition en suspendant l'exécution du  thread  jusqu'à  ce qu'un autre thread signale la condition.

Une  variable  condition  doit  toujours être associée à un mutex (sémaphore d'exclusion mutuelle), pour éviter une condition concurrente où un thread se prépare à attendre une condition  et  un  autre thread signale la condition juste avant que le premier n'attende réellement.

Il peut arriver qu'une condition soit placée sur une donnée partagée par plusieurs tâches. Ainsi, suivant les besoins, une tâche accédant à la donnée peut être endormie si la condition n'est pas vérifiée. Elle ne sera réveillée que lorsqu'une autre tâche accédera à cette donnée et rendra la condition vraie.

Les principaux éléments à connaître sur les variables conditions sont les suivants :

1. La déclaration et l'initialisation de la variable condition : pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
2. La primitive permettant d'endormir une tâche (possédant le verrou sur la donnée partagée) si la condition cond est fausse : int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *verrou)
3. La primitive permettant de rendre la condition cond vraie. Cela envoie un signal de réveil aux tâches qui ont été endormies sur cette condition : `int pthread_cond_signal(pthread_cond_t *cond)`

Si plusieurs tâches attendent sur une condition, l'utilisation de pthread_cond_signal(pthread_cond_t *cond) ne réveille que l'une d'entre elles. Les autres restent malheureusement endormies. Pour réveiller toutes les tâches, on utilise la fonction suivante : int `pthread_cond_broadcast(pthread_cond_t *cond)`

