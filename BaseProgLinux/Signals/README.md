# Signaux Linux

## Le signal est une interruption logicielle.
* Il informe les processus de l'occurrence d'événements asynchrones.
* Il ne transporte pas d'informations.
* Le processus qui le prend en compte exécute un traitement.

* L'événement associé à un signal
  * extérieur au processus (frappe caractère, terminaison d'un autre processus)
  * intérieur au processus correspondant à une erreur (erreur arithmétique ou violation mémoire) : levée d'une trappe.



## 64 signaux identifiés par un numéro et un nom (SIGX)
* 1 à 31 : signaux classiques
* 32 à 63 : signaux temps réel



Voici le sens de quelques signaux de la norme POSIX

* signaux relatifs à la fin de processus :
  * SIGCHLD (17) : mort du fils
  * SIGKILL (9) : signal de terminaison

* signaux relatifs à des erreurs
  * SIGILL (4) : instruction illégale
  * SIGFPE (8) : erreur arithmétique
  * SIGSEGV (11) : violation mémoire
  * SIGPIPE (13) : écriture dans un tube sans lecteur

* signaux relatifs aux temporisations
  * SIGALRM (14): fin de temporisation (fonction alarm)

* signaux relatifs aux interactions avec le terminal (extinction, frappe touche DELETE et BREAK)
  * SIGHUP, SIGINT (crtl C), SIGQUIT (crtl \)

* Deux signaux disponibles pour les utilisateurs (SIGUSR1, SIGUSR2)

Voici une liste "brute" des signaux disponible dans Linux (Ubuntu 17.04)

```Bash
$> kill -l
 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX	
```
# Les primitive pour la manipulation des signaux

* Envoyer un signal à un processus
  * int kill (pid_t pid, int sig) `kill (12563, SIGKILL)`
  * kill -n°signal pid  (commande shell)       `kill -9 12563`


* Associer un handler à un signal
  * signal(int sig, fonction) signal(SIGINT, p_hand)
  * sigaction(int sig, struct sigaction action, NULL)
* Armer une temporisation
  * int alarm (int seconds) : alarm(10) au bout de seconds unités de temps, le signal SIGALRM est envoyé au processus
* Attendre un signal
  * int pause();

  ## Vers les exemples 

  * [Exemples signaux Linux](Exemples.md)