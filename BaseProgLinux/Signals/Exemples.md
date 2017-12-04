# Les primitives

* [sigaction](#sigaction)

# sigaction 
Examiner et modifier l'action associée à un signal

```
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```


## DESCRIPTION
L'appel système sigaction() sert à modifier l'action effectuée par un processus à la réception d'un signal spécifique. (Consultez signal(7) pour une vue d'ensemble sur les signaux)

signum indique le signal concerné, à l'exception de SIGKILL et SIGSTOP.

Si act n'est pas NULL, la nouvelle action pour le signal signum est définie par act. Si oldact n'est pas NULL, l'ancienne action est sauvegardée dans oldact.

La structure sigaction est définie par quelque chose comme :

```C
struct sigaction {
    void     (*sa_handler)(int); /* SIG_DFL ou SIG_IGN ou pointeur sur handler */
    void     (*sa_sigaction)(int, siginfo_t *, void *); /* un handler plus complet avec plus d'informations */
    sigset_t   sa_mask; /* masque sur signaux */
    int        sa_flags; /* mettre a null */
};
```


sa_handler  indique  l'action  affectée  au  signal  signum,  et peut être SIG_DFL pour l'action par défaut, SIG_IGN pour ignorer le signal, ou un pointeur sur une fonction de gestion de signaux.

## siginfo
La structure siginfo_t dans le cas d'utilisation sa_sigaction plus riche que sa_handler
```C
siginfo_t {
    int      si_signo;    /* Numéro de signal*/
    int      si_errno;    /* Numéro d'erreur */
    int      si_code;     /* Code du signal  */
    int      si_trapno;   /* Numéro de trappe qui a causé
       le signal généré par le
       matériel (pas utilisé sur la
       plupart des architectures) */
    pid_t    si_pid;      /* PID de l'émetteur          */
    uid_t    si_uid;      /* UID réel de l'émetteur     */
    int      si_status;   /* Valeur de sortie ou signal */
    clock_t  si_utime;    /* Temps utilisateur écoulé   */
    clock_t  si_stime;    /* Temps système écoulé       */
    sigval_t si_value;    /* Valeur de signal*/
    int      si_int;      /* Signal POSIX.1b */
    void    *si_ptr;      /* Signal POSIX.1b */
    int      si_overrun;  /* Décompte de dépassement des
       horloges (POSIX.1b)        */
    int      si_timerid;  /* ID d'horloge (POSIX.1b)    */
    void    *si_addr;     /* Emplacement mémoire ayant
       causé l'erreur  */
    long     si_band;     /* Band event (était int dans
       glibc 2.3.2 et antérieures */
    int      si_fd;       /* Descripteur de fichier     */
    short    si_addr_lsb; /* Bit le moins significatif de l'adresse
       (depuis Linux 2.6.32)   */
}

```
## utilisation courante

soit 
```C
void p_hand (int sigid){
    //Faire quelque chose
}

void p_action(int sig, siginfo_t *siginfo, void *context) {
    //Faire quelque chose
}
```
quelque part dans le code on associie un handler a un signal
```C
struct sigaction action;
action.sa_handler = p_hand; /* p_hand une pointeur sur la fonction associé au signal */
/* OU mais pas les 2 ! */
action.sa_sigaction = &p_action;
sigaction (SIG_INT, &action, NULL);
```

## Un premier exemple

* [Exemple avec sigaction sa_handler et sa_sigaction](exempleSigaction.c)


# kill
kill - Envoyer un signal à un processus

```C
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);
```

## DESCRIPTION
L'appel système kill() peut être utilisé pour envoyer n'importe quel signal à n'importe quel processus ou groupe de processus.

Si pid est positif, le signal sig est envoyé au processus dont l'identifiant est indiqué par pid.

# signal
signal - Gestion de signaux ANSI C

```C
#include <signal.h>
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
```

## DESCRIPTION
Le  comportement  de  signal()  varie  selon les versions d'UNIX, et a aussi varié au cours du temps dans les différentes versions de Linux. Évitez de l'utiliser : utilisez plutôt [sigaction](#sigaction).

signal() installe le gestionnaire handler pour le signal signum. handler peut être SIG_IGN, SIG_DFL ou  l'adresse  d'une  fonction  définie  par  le  programmeur  (un  « gestionnaire  de signal »).

Lors de l'arrivée d'un signal correspondant au numéro signum, l'un des événements suivants se produit :
*  Si le gestionnaire vaut SIG_IGN, le signal est ignoré.
*  Si le gestionnaire est SIG_DFL, l'action par défaut associée à ce signal est entreprise (consultez signal(7)).

Dans  les systèmes UNIX d'origine, quand un gestionnaire défini par signal() était appelé lors de la distribution d'un signal, le gestionnaire du signal était remis à SIG_DFL, et le système ne bloquait pas la distribution des instances suivantes du signal. Cela revenait à appeler sigaction(2) avec les attribut suivants :

`sa.sa_flags = SA_RESETHAND | SA_NODEFER;`

__Dans les exemples avec la version Linux ubuntu 17.04 le comportement est différent!__
[Linux programmation système (Index)](http://lps.cofares.net/)
