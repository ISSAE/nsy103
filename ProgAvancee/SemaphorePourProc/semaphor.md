

**<u><font size="+2" face="Arial">Les Sémaphores</font></u>**
1.  <a name="_Toc360512225"><font size="4" face="Arial">Description</font></a>

    La plus importante contribution au problème de la synchronisation entre processus fut l'introduction par _**Dijkstra**_, en _**1965**_, du concept des Sémaphores.

    Conceptuellement, un sémaphore joue le rôle d'un _**distributeur de tickets**_, qui, initialement dispose d'un certain nombre de tickets, éventuellement nul.

    Un processus utilisateur du sémaphore _**demande un ticket**_ en _**invoquant**_ une opération particulière appelée _**P**_ : _**si**_ au moins _**un ticket est disponible**_, le processus appelant _**le prend et poursuit**_ son exécution ; _**dans le cas contraire**_, le demandeur est enregistré dans une file d'attente et _**est bloqué**_ dans l'attente de l'obtention d'un ticket. Autrement dit, _**l'opération P**_ n'est exécutable par le processus appelant _**que s'il existe un ticket libre**_, elle _**peut se retrouver bloquante**_ dans le cas contraire.

    Grâce à une _**opération inverse**_, appelée _**V**_, un processus _**dépose son ticket**_ dans le distributeur. _**Si**_ des _**processus**_ sont _**en attente**_ dans la file du sémaphore, _**le premier**_ d'entre eux _**est débloqué**_ et obtient son ticket.

    Plus précisément, un sémaphore est une _**variable entière <u>non négative</u>**_ à laquelle, sauf pour l'initialisation, on accède _**seulement à travers deux opérations**_ standards atomiques (non interruptibles) : _**P et V**_.

    *   _**P**_, de l'hollandais proberen (tester), aussi appelé parfois wait, consiste à _**décroître la valeur du sémaphore**_ d'une unité _**à condition**_ que le résultat ne devienne <u>_**pas négatif**_</u>. En effet, _**dans le cas**_ ou un processus effectue P et que la _**valeur**_ du sémaphore est _**de zéro**_, alors ce dernier _**se retrouve gelé**_ jusqu'à ce que cette valeur redevienne supérieur strictement à zéro et qu'il puisse alors la décrémenter.

    <
    *   _**V**_, pour  Verhogen  (incrémenter), aussi appelé parfois signal, consiste simplement à _**accroître la valeur du sémaphore**_ d'une unité.

    
    Ce mécanisme _**permet**_ donc de _**limiter l'exécution d'une portion de code** _(et donc l'accès à une ressource quelconque), encadrée par des appels respectifs à P et à V, _**à un nombre fixé**_ de processus. Nous allons voir par la suite, que cela permet de réaliser l'exclusion mutuelle nécessaire à la prévention des conflits d'accès aux données non partageables.


        1.  <a name="_Ref360503486"><font face="Arial">Les sémaphores sous Linux</font></a>
        2.  <font size="2" face="Arial">présentation</font>

            La gestion des sémaphores sous Unix, est prise en compte par des _**primitives systèmes**_ (system calls) étant donné leur principe de fonctionnement très bas niveau et la nécessité d'avoir les opérations P et V qui ne soient pas interruptibles. Les sémaphores sont donc gérés par le noyau, ils appartiennent à la classe des objets IPC.

            La technique IPC Unix système V, propose un ensemble de mécanismes purement mémoires, qui permettent dans des limites de droits, à n'importe quels couples de processus _**d'échanger des informations et/ou de se synchroniser**_. Les objets IPC sont composés en :

            *   des _**files de messages**_, aussi appelées queues de messages ("messages", abrégé msg),

            Les processus ont le loisir de créer une file d'attente, de la supprimer, d'y ajouter ou d'en retirer un message. Ces files gérées directement dans l'espace noyau recevront des messages de différents types et tailles.

            *   des _**mémoires partagées**_ ("shared memory", abrégé shm),

            Les mémoires partagées sont des segments de mémoire qui peuvent, comme leur nom l'indique être partagé par plusieurs processus, avec les problèmes d'exclusion mutuelle que peut impliquer.

            *   et des _**sémaphores**_ ("semaphore", abrégé sem),

            Sémaphores que l'on ne présente plus...

            Le point commun des objets IPC, et qui nous intéresse plus particulièrement en ce qui concerne les sémaphores, est qu'ils forment des _**ressources maintenues par le noyau**_ dans son espace personnel ; ils sont donc _**indépendants d'un processus particulier**_. Chaque processus ne fait que requérir auprès du noyau l'obtention et l'utilisation de ceux-ci.

            A cette double fin (centralisation et partage), Unix maintient pour type d'objet IPC, une table personnelle identifiant chacune des instances crées. Ceci explique pourquoi, les files de messages, les mémoires partagées et les sémaphores sont _**tous identifiés sous la forme d'un entier**_ (type <tt>int</tt>) souvent appelé xxxid (ou xxx est soit msg pour les files, shm pour les mémoires ou sem pour les sémaphores).

            L'IPC sémaphore d'Unix possède deux généralisations qui en enrichissent encore la puissance.

            *   _**Incrémentation**_ et _**décrémentation**_ d'un sémaphore _**par un entier quelconque**_.
            *   _**Possibilité**_ _**d'agir**_ sur _**plusieurs sémaphores**_ de manière atomique (non-interruptible), _**un IPC de type sémaphore**_ gèrant par conséquence <u>_**non pas un seul**_</u> sémaphore, mais <u>_**un tableau de sémaphore**_</u>, chacun étant identifié par son rang dans le tableau (0 pour le premier).
        3.  <font size="2" face="Arial">création ou acquisition</font>

            Pour créer, ou acquérir un sémaphore, on dispose de la primitive suivante :

            <center><tt>int semget(key_t cle, int nsems, int semflag);</tt></center>

            Cette fonction _**crée le sémaphore**_ si celui-ci n'existe pas, _**ou renvoie un identificateur**_ sur ce dernier _**s'il a déjà été créé**_ par un autre processus.

            Description des paramètres :

            *   <tt>cle</tt>, constante symbolique pour identifier le sémaphore à sa création
            *   <tt>nsems</tt>, est le nombre de sémaphore(s) souhaité(s) dans le tableau
            *   <tt>semflag</tt>, représente les droits souhaités, généralement : <tt>IPC_CREAT | 0700</tt>

            En retour, la fonction renvoie soit -1 si une erreur c'est produite, ou alors l'identificateur (semid) du sémaphore.

            Ex. pour créer un sémaphore simple :

            <center><tt>semid = semget(cle, 1, IPC_CREAT | 0700);</tt></center>

        4.  <font size="2" face="Arial">initialisation</font>

            Pour affecter une valeur initiale à un sémaphore, on utilise la primitive <tt>semctl()</tt>, qui permet aussi entre autre, comme nous le verrons plus tard, de libérer un sémaphore.

            <center><tt>int semctl(int semid, int semnum, SETVAL, int valeur);</tt></center>

            Description des paramètres :

            *   <tt>semid</tt>, identificateur du sémaphore au niveau du système (voir précédemment)
            *   <tt>semnum</tt>, indice du sémaphore dans le sous-ensemble
            *   <tt>SETVAL</tt>, pour indiquer au noyau que l'on désire affecter une valeur au sémaphore
            *   <tt>valeur</tt>, valeur initiale

            En retour, la fonction renvoie soit -1 si une erreur s'est produite.

            Ex. pour initialiser un sémaphore simple à 1 (identifié par <tt>semid</tt>) :

            <center><tt>valRet = semctl(semid, 0, SETVAL, 1);</tt></center>

        5.  <font size="2" face="Arial">utilisation</font>

            En ce qui concerne les opérations P et V, elles peuvent être réalisées par des appels directs à la primitive système <tt>semop()</tt>, de la manière suivante :

            <tt>void p(int semid)</tt>

            <tt>{</tt>

            <tt>int rep;</tt>

            <tt>struct sembuf pd={0,-1,0};
            </tt>

            <tt>rep=semop(semid, &pd, 1);
            </tt>

            <tt>return(rep);</tt>

            <tt>}</tt>

            <tt>void v(int semid)</tt>

            <tt>{</tt>

            <tt>int rep;</tt>

            <tt>struct sembuf pd={0,1,0};
            </tt>

            <tt>rep=semop(semid, &pd, 1);
            </tt>

            <tt>return(rep);</tt>

            <tt>}</tt>

            <u>NB :</u> il est _**très important**_ pour le bon fonctionnement de ces deux opérations, que _**leur code ne comportent uniquement que des appels à** _<tt>_**<font size="2" face="Courier New">semop()</font>**_</tt> et rien de plus, car seul le déroulement de cette primitive est garanti comme n'étant pas interruptible par le noyau ! Cette précaution est nécessaire pour préserver le caractère atomique de ces deux opérations.

            La primitive <tt>semop()</tt> permet d'augmenter ou de diminuer la valeur d'un sémaphore, et comme nous l'avons vu précédemment, elle peut le faire avec un nombre d'une valeur quelconque et sur un sémaphore qui peut éventuellement être décomposé en un sous-ensemble de sémaphore.

            <center><tt>int semop(int semid, struct sembuf *sops, size_t nsops);</tt></center>

            Description des paramètres :

            *   <tt>semid</tt>, identificateur du sémaphore au niveau du système
            *   <tt>sops</tt>, est une structure composée de 3 nombres :
                *   <tt>sem_num</tt>, l'indice de départ du (ou des) sémaphore(s) à traiter,
                *   <tt>sem_op</tt>, la valeur à appliquer au sémaphore,
                *   et <tt>sem_flg</tt>, un drapeau (flag) qui sera renseigné par le système.
            *   <tt>nsops</tt>, nombre de sémaphore(s) a traiter (à partir de l'indice de départ de <tt>sops</tt>)

            Dans le cas présent, un seul sémaphore (non décomposable) nous suffit, donc la plupart de ces paramètres sont à zéro.

            _**L'action**_ réelle de <tt>semop()</tt>_**dépend de la valeur du paramètre** _<tt>_**<font size="2" face="Courier New">sem_op</font>**_</tt> :

            *   si celle-ci est _**strictement supérieur à 0**_, alors elle est _**ajoutée à celle du sémaphore**_. Les processus en attente de l'augmentation du sémaphore sont réveillées par Unix.
            *   si par contre elle est _**strictement inférieur à 0**_, alors la _**valeur**_ absolue de <tt>sem_op</tt> est _**retirée du sémaphore**_. Dans le cas ou cette absolue est plus grande que celle du sémaphore, alors le processus s'endort.
            *   enfin, dans le cas ou la valeur transmise est _**égal à 0**_, cela permet de _**tester si le sémaphore est à 0**_ et donc de déterminer éventuellement _**si l'opération P**_ sera _**bloquante**_.

            Ainsi, dans les définitions précédentes de P et de V, on peut remarquer que le paramètre <tt>sem_op</tt> prend respectivement la valeur -1 (pour décrémenter le sémaphore) et la valeur 1 (pour l'incrémenter).

            <u>_Remarque:_</u>

            *   au niveau du noyau, les _**processus endormis**_ sous placé dans une file d'attente similaire à celle qui regroupe les processus en attente d'une entrée / sortie, ils _**ne consomment**_ donc _**plus de temps CPU**_.
            *   les processus _**sommeillent**_ dans un _**mode <u>interruptible</u>**_, ils sont donc _**sensible aux signaux**_ !
            *   on peut implémenter différentes options, telle que l'opération P immédiate (voir la partie Quelques variantes à la page 13), grâce à certains paramètres tels que le flag <tt>IPC_NOWAIT</tt> qui permet de ne pas rendre <tt>semop()</tt> bloquant et d'être averti de l'échec de ce dernier.
        6.  <font size="2" face="Arial">libération</font>

            La libération d'un sémaphore est faite par un appel à <tt>semctl()</tt>, a qui l'on transmet l'identificateur du sémaphore, ainsi que la commande <tt>IPC_RMID</tt>.

            <center><tt>int semctl(int semid, IPC_RMID, NULL);</tt></center>

            Description des paramètres :

            *   <tt>semid</tt>, identificateur du sémaphore au niveau du système
            *   <tt>IPC_RMID</tt>, pour indiquer au noyau que l'on souhaite supprimer le sémaphore

            En retour, la fonction renvoie soit -1 si une erreur s'est produite.

            Ex. pour libérer un sémaphore (identifié par <tt>semid</tt>) :

            <center><tt>valRet = semctl(semid, IPC_RMID, NULL);</tt></center>

        7.  <a name="_Toc360512230"><font size="4" face="Arial">Les risques liés à l'emploi des sémaphores</font></a>

            Bien que les sémaphores fournissent des _**mécanismes pratiques et efficaces**_ (en temps machine) pour la synchronisation de processus, leur _**utilisation incorrecte**_ peut encore _**provoquer de nombreuses erreurs**_ de synchronisation _**difficiles à détecter**_, puisque ces erreurs surviennent seulement si certaines séquences d'exécution particulières ont lieu. Une difficulté supplémentaire et pernicieuse étant le fait que ces séquences erronées ne se produisent pas toujours.

            Afin d'illustrer comment, étudions à nouveau la solution au problème de la section critique avec des sémaphores. Tous les processus partagent une variable sémaphore : mutex, initialisée à 1\. Chaque processus doit exécuter un P(mutex) avant de rentrer dans la section critique, et un V(mutex) après. Si l'on ne respecte pas cette séquence, les deux processus peuvent se trouver dans leur sections critiques simultanément, ou en arriver à un situation de blocage, ou d'interblocage.

        8.  <font face="Arial">Inversion des opérations P et V</font>

            Supposons qu'un processus permute l'ordre d'exécution des opérateurs P et V sur le sémaphore d'exclusion mutuelle, ce qui provoque l'exécution suivante :

            <tt>V(mutex)</tt>

            ...

            section critique

            ...

            <tt>P(mutex)</tt>

            Dans cette situation, _**plusieurs processus**_ peuvent s'exécuter _**simultanément**_ _**dans**_ leur _**sections critiques**_, violant ainsi le besoin de l'exclusion mutuelle. On peut aussi découvrir cette erreur si plusieurs processus sont actifs en même temps dans leur sections critiques, mais cette situation peut ne pas toujours se reproduire !

        9.  <font face="Arial">Substitution d'un appel V par un appel à P</font>

            Supposons maintenant, qu'un processus remplace un appel à V (remise du ticket) par un appel à P (prise du ticket), c'est à dire qu'il exécute deux fois P :

            <tt>P(mutex)</tt>

            ...

            section critique

            ...

            <tt>P(mutex)</tt>

            Dans ce cas, il se produira irrémédiablement un _**blocage sur le second P**_.

        10.  <font face="Arial">Encore pire ...</font>

            Supposons enfin, qu'un processus omette l'appel à V ou à P, ou les deux. Dans ce cas, soit on viole l'exclusion mutuelle, soit il se produira un blocage du processus par lui-même, comme nous venons de le voir précédemment, soit les processus se bloque les uns les autres (interblocage).

        11.  <font face="Arial">Conclusion</font>

            Ces exemples montrent que plusieurs types d'erreurs peuvent se générer facilement quand les sémaphores sont utilisés incorrectement pour résoudre, entre autre, le problème de la section critique.

            Ces cas peuvent sembler évident et facile à déceler lorsqu'ils sont isolés comme ici, mais dans l'hypothèse d'un projet volumineux, employant éventuellement plusieurs sémaphores simultanément, et se déroulant de manière assez difficile à prévoir, ils peuvent facilement se glisser dans des séquences d'instructions et être très complexe à déceler.

            De plus, si un programmeur ne s'aperçoit pas qu'une structure de données particulière doit être partagée entre différents processus, il omettra d'encadrer les sections critiques par des opérateurs P et V, et cette structure sera exposée aux risques de corruption exposés dans la section 1.2.

            Une des solutions introduites, _**pour remédier à ces inconvénients**_, fut l'apparition d'une autre structure de synchronisation de plus haut niveau : _**les Moniteurs**_, que nous examinerons par la suite, dans la section 4 à la page 26.

* * *
