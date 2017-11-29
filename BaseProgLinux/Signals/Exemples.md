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
