[Index (Home)](/) | [API SGF](..)
------------------| -------------

# OPEN

## NOM
open, openat, creat - Ouvrir ou créer éventuellement un fichier

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

## DESCRIPTION
Étant donné le chemin pathname d'un fichier, open() renvoie un descripteur  de  fichier (petit entier positif ou nul) qui pourra ensuite être utilisé dans d'autres  appels  système  (read(2),  write(2),  lseek(2), fcntl(2),  etc.). Le descripteur de fichier renvoyé par un appel réussi sera le plus petit descripteur de fichier non actuellement  ouvert  par le processus.

Par défaut, le nouveau descripteur de fichier est configuré pour rester ouvert après un appel à execve.  La  position dans le fichier est définie au début du fichier.

Un  appel à open() crée une nouvelle description de fichier ouvert, une entrée dans la table de fichiers ouverts du système. Cette entrée enregistre  la  position dans le fichier et les attributs d'état du fichier.  Un  descripteur de fichier  est  une  référence (dans le contexte du processus) à  l'une de ces entrées;

Le  paramètre  flags est l'un des éléments O_RDONLY, O_WRONLY ou O_RDWR qui réclament respectivement l'ouverture du fichier en  lecture  seule, écriture seule, ou lecture/écriture.

De  plus,  zéro ou plusieurs attributs de création de fichier et attributs d'état de fichier peuvent être indiqués  dans  flags  avec  un  OU binaire (`en C c'est |`).  Les attributs de création de fichier sont O_CLOEXEC, O_CREAT,O_DIRECTORY,  O_EXCL,  O_NOCTTY,  O_NOFOLLOW,  O_TMPFILE,  O_TRUNC   et O_TTY_INIT. Les attributs d'état de fichier sont tous les autres attributs indiqués ci-dessous.

La liste complète des attributs de création et d'état de fichier est la suivante.

**O_APPEND** :
Le  fichier est ouvert en mode « ajout ». Initialement, et avant chaque write(2), la tête de lecture/écriture est placée à la fin du fichier comme avec lseek(2). Il y a un risque d'endommager le
fichier lorsque O_APPEND est utilisé, sur un système de fichiers
NFS, si plusieurs processus tentent d'ajouter des données simul‐
tanément au même fichier. Ceci est dû au fait que  NFS  ne  sup‐
porte  pas l'opération d'ajout de données dans un fichier, aussi
le noyau du client est obligé de la simuler, avec un  risque  de
concurrence des tâches.

**O_ASYNC**:
Déclencher  un  signal  (SIGIO par défaut, mais peut être changé
via fcntl(2)) lorsque la lecture ou l'écriture  deviennent  pos‐
sibles sur ce descripteur. Ceci n'est possible que pour les terminaux, pseudoterminaux, sockets et (depuis Linux 2.6) tubes  et
FIFO.  Consultez  fcntl(2) pour plus de détails. Consultez aussi
BOGUES ci-dessous.

**O_CLOEXEC**: (depuis Linux 2.6.23)
Activer l'attribut « close-on-exec » pour le nouveau descripteur
de  fichier.  

**O_CREAT**:
Créer  le  fichier  s'il  n'existe  pas.  Le possesseur (UID) du
fichier est renseigné  avec  l'UID  effectif  du  processus.  Le
groupe propriétaire (GID) du fichier est le GID effectif du processus ou le GID du répertoire parent (cela dépend du système de
fichiers, des options de montage, du mode du répertoire parent ;
consultez  les  options  de  montage  bsdgroups  et   sysvgroups
décrites dans la page mount(8)).

Le  paramètre  mode  indique les droits à utiliser si un nouveau
fichier est créé. Ce paramètre doit être fourni quand O_CREAT ou
**O_TMPFILE**   sont indiqués dans flags ; si ni O_CREAT ni O_TMPFILE
ne sont précisés, mode est ignoré.  Les  droits  effectifs  sont
modifiées par le umask du processus : la véritable valeur utilisée est (mode & ~umask). Remarquez que  ce  mode  ne  s'applique
qu'aux  accès  ultérieurs  au fichier nouvellement créé. L'appel
open() qui crée un fichier dont le mode  est  en  lecture  seule
fournira  quand  même  un  descripteur  de fichier en lecture et
écriture.

Les  constantes  symboliques  suivantes  sont  disponibles  pour mode :

* S_IRWXU  00700  L'utilisateur  (propriétaire  du  fichier) a les
  autorisations de lecture, écriture, exécution.
* S_IRUSR  00400 L'utilisateur a l'autorisation de lecture.
* S_IWUSR  00200 L'utilisateur a l'autorisation d'écriture.
* S_IXUSR  00100 L'utilisateur a l'autorisation d'exécution.
* S_IRWXG  00070 Le groupe a les autorisations de  lecture,  écriture, exécution.
* S_IRGRP  00040 Le groupe a l'autorisation de lecture.
* S_IWGRP  00020 Le groupe a l'autorisation d'écriture.
* S_IXGRP  00010 Le groupe a l'autorisation d'exécution.
* S_IRWXO  00007  Tout  le  monde  a les autorisations de lecture,écriture, exécution.
* S_IROTH  00004 Tout le monde a l'autorisation de lecture.
* S_IWOTH  00002 Tout le monde a l'autorisation d'écriture.
* S_IXOTH  00001 Tout le monde a l'autorisation d'exécution.

**O_DIRECT**: (depuis Linux 2.4.10)
Essayer de minimiser les effets du cache d'entrée-sortie sur  ce
fichier.  Cela  dégradera  en général les performances, mais est
utile dans des situations spéciales, comme lorsque les  applica‐
tions ont leur propre cache. Les entrées-sorties de fichier sont
faites directement de et vers les tampons d'espace  utilisateur.
L'ajout de l'attribut O_DIRECT fait que les entrées-sorties sont
synchrones ; en réalité un effort est fait pour rendre le trans‐
fert  synchrone  mais  cela  n'offre pas la garantie fournie par
l'attribut O_SYNC que les données et métadonnées  sont  transférées.  Pour  garantir des entrées-sorties synchrones, l'attribut O_SYNCdoit être utilisé en plus de l'attribut O_DIRECT. Consul‐
tez la section NOTES ci-dessous.

Une  interface  à  la sémantique similaire (mais dépréciée) pour
les périphériques blocs est décrite à la page raw(8).

**O_DIRECTORY** 
Si pathname n'est pas un  répertoire,  l'ouverture  échoue.  Cet
attribut  fut ajouté dans la version 2.1.126 du noyau, pour évi‐
ter des problèmes de dysfonctionnement si opendir(3) est invoqué
sur une FIFO ou un périphérique de bande.

**O_DSYNC** 
Les  opérations  d'écriture dans le fichier se dérouleront selon
les conditions d'exécution des opérations  E/S  synchrones  avec
garantie d'intégrité des données.
Au  moment  où write(2) (ou un appel similaire) renvoie une don‐
née, elle a été  transmise  au  matériel  sur  lequel  s'exécute
l'appel,  avec  toutes les métadonnées du fichier qui pourraient
être nécessaires à la récupération de cette donnée (c'est à dire
comme si chaque appel à write(2) était suivi d'un appel à fdata‐
sync(2)). Consultez NOTES ci-dessous.

**O_EXCL**  S'assurer que cet appel crée le fichier : si  cet  attribut  est
spécifié  en  conjonction avec O_CREAT et si le fichier pathname
existe déjà, open() échouera.

Lorsque ces deux attributs sont spécifiés, les liens symboliques
ne  sont pas suivis : si pathname est un lien symbolique, open()
échouera quelque soit l'endroit où pointe le lien symbolique.

En général, le comportement de O_EXCL est indéterminé  s'il  est
utilisé sans O_CREAT. Il existe une exception toutefois : à par‐
tir de Linux 2.6, O_EXCL peut être utilisé sans O_CREAT si path‐
name  fait  référence à un périphérique bloc. Si le périphérique
bloc est utilisé par le système (par exemple, s'il  est  monté),
open() échoue avec l'erreur EBUSY.
Sur  les  systèmes  de fichiers NFS, O_EXCL n'est pris en charge
qu'avec la version NFSv3 ou ultérieure, sur les  noyaux  2.6  ou
plus  récents. Dans les environnements NFS où la prise en charge
d'O_EXCL n'est pas fournie, les programmes  qui  ont  besoin  de
cette  fonctionnalité  pour  verrouiller  des tâches risquent de
rencontrer une concurrence critique (race condition).  Les  pro‐
grammes  portables qui veulent effectuer un verrouillage fichier
atomique en utilisant un fichier verrou et qui doivent éviter la
dépendance  de  la prise en charge NFS pour O_EXCL peuvent créer
un fichier unique sur le même système de fichiers (par  exemple,
avec le PID et le nom de l'hôte), et utiliser link(2) pour créer
un lien sur un fichier de verrouillage. Si link(2) renvoie 0, le
verrouillage  est réussi. Sinon, utiliser stat(2) sur ce fichier
unique pour vérifier si le nombre de liens a augmenté jusqu'à 2,
auquel cas le verrouillage est également réussi.pour vérifier si
le nombre de liens a augmenté jusqu'à  2.  Ne  pas  utiliser  la
valeur de retour de link(2).

**O_LARGEFILE** 
(LFS)  Permet  d'ouvrir  des fichiers dont la taille ne peut pas
être représentée  dans  un  off_t  (mais  peut  l'être  dans  un
off64_t).  La macro _LARGEFILE64_SOURCE doit être définie (avant
d'inclure tout fichier d'en‐tête) pour obtenir cette définition.
Définir la macro _FILE_OFFSET_BITS à 64 est la méthode à favori‐
ser pour accéder à des grands fichiers sur des systèmes 32 bits,
plutôt    que    d'utiliser    O_LARGEFILE    (consultez    fea‐
ture_test_macros(7)).

**O_NOATIME**  (depuis Linux 2.6.8)
Ne pas mettre à jour l'heure de dernier accès au fichier  (champ
st_atime  de  l'inœud)  quand le fichier est lu avec read(2). Ce
attribut est seulement conçu pour les programmes d'indexation et
d'archivage,  pour  lesquels  il  peut réduire significativement
l'activité du disque. L'attribut peut ne pas être  effectif  sur
tous  les  systèmes  de fichiers. Par exemple, avec NFS, l'heure
d'accès est mise à jour par le serveur.

**O_NOCTTY** 
Si pathname correspond à un périphérique de terminal — consultez
tty(4) —,  il ne deviendra pas le terminal contrôlant le proces‐
sus même si celui-ci n'est attaché à aucun autre terminal.

**O_NOFOLLOW** 
Si pathname est un lien symbolique,  l'ouverture  échoue.  C’est
une  extension  FreeBSD,  qui  fut  ajoutée à Linux dans la ver‐
sion 2.1.126. Les liens symboliques se trouvant dans  le  chemin
d'accès proprement dit seront suivis normalement. Consultez éga‐
lement O_PATH dans la suite du document.

**O_NONBLOCK  ou O_NDELAY**
Le fichier est ouvert en mode « non-bloquant ». Ni  la  fonction
open()  ni  aucune  autre opération ultérieure sur ce fichier ne
laissera le processus appelant en attente. Pour la  manipulation
des FIFO (tubes nommés), voir également fifo(7). Pour une expli‐
cation de l'effet de O_NONBLOCK en  conjonction  avec  les  ver‐
rouillages impératifs et les baux de fichiers, voir fcntl(2).


**O_SYNC**  Les  opérations  d'écriture dans le fichier se dérouleront selon
les conditions d'exécution des opérations  E/S  synchrones  avec
garantie d'intégrité du fichier (contrairement à l'exécution des
opérations E/S synchrones avec garantie d'intégrité des  données
fournie par O_DSYNC.)

Au  moment  où write(2) (ou un appel similaire) renvoie une don‐
née, cette donnée et les métadonnées associées  au  fichier  ont
été  transmises au matériel sur lequel s'exécute l'appel (autre‐
ment dit, comme si chaque appel  à  write(2)  était  suivi  d'un
appel à fsync(2)). Consultez NOTES ci-dessous.

**O_TMPFILE**  (depuis Linux 3.11)
Créer  un  fichier  temporaire  sans  nom.  L’argument  pathname
indique un répertoire ; un inœud sans nom sera créé dans le sys‐
tème de fichiers de ce répertoire. Tout ce qui est écrit dans le
fichier résultant sera perdu quand  le  dernier  descripteur  de
fichier sera fermé, à moins de donner un nom au fichier.

**O_TMPFILE**   doit être indiqué avec soit O_RDWR, soit O_WRONLY, et
facultativement O_EXCL. Si O_EXCL s’est pas indiqué, alors  lin‐
kat(2) peut être utilisé pour lier le fichier temporaire dans le
système de fichier, le rendant permanent, en utilisant  du  code
comme :

    char chemin[PATH_MAX];
    df = open("/chemin/vers/rép.", O_TMPFILE | O_RDWR,
S_IRUSR | S_IWUSR);

    /* Entrée et sortie du fichier sur « df »… */

    snprintf(chemin, PATH_MAX,  "/proc/self/fd/%d", df);
    linkat(AT_FDCWD, chemin, AT_FDCWD, "/chemin/vers/fichier",
AT_SYMLINK_FOLLOW);

Dans  ce  cas,  l’argument  mode  d’open()  détermine le mode de
droits du fichier, comme avec O_CREAT.

Indiquer O_EXCL en conjonction avec O_TMPFILE empêche de lier un
fichier  temporaire  dans le système de fichiers comme précédem‐
ment (remarquez que la signification de O_EXCL dans ce  cas  est
différente de la signification habituelle de O_EXCL).

Les  deux principaux cas d’utilisation de O_TMPFILE sont présen‐
tés ci-dessous :

*  Améliorer la fonctionnalité tmpfile(3) : création de fichiers
   temporaires  sans situation de compétition qui (1) sont auto‐
   matiquement supprimés à la fermeture ; (2) ne peuvent  jamais
   être  atteints  par leur chemin ; (3) ne sont pas exposés aux
   attaques de lien symbolique ; et  (4) ne  nécessitent  pas  à
   l’appelant d’inventer des noms uniques.

*  Créer un fichier initialement invisible, qui est ensuite peu‐
   plé de données et ajusté aux attributs de système de fichiers
   adéquats   (chown(2),   chmod(2),  fsetxattr(2), etc.)  avant
   d’être automatiquement lié dans le système de  fichiers  dans
   un  état  complètement  formé  (en  utilisant linkat(2) comme
   décrit précédemment).

**O_TMPFILE**  nécessite une  prise  en  charge  par  le  système  de
fichiers  sous-jacent.  Seul une partie des systèmes de fichiers
Linux fournit cette prise en charge. Dans l'implémentation  ini‐
tiale,  la  prise  en  charge était assurée pour les systèmes de
fichiers ext2, ext3, ext4, UDF, Minix et shmem. XFS  est  égale‐
ment pris en charge depuis Linux 3.15.

**O_TRUNC** 
Si  le  fichier  existe, est un fichier ordinaire et que le mode
d’accès permet l’écriture (O_RDWR ou O_WRONLY), il sera  tronqué
à  une longueur nulle. Si le fichier est une FIFO ou un périphé‐
rique terminal, l'attribut O_TRUNC est ignoré. Sinon, le compor‐
tement  de O_TRUNC n'est pas précisé. Sur de nombreuses versions
de Linux, il sera ignoré ; sur d'autres versions il  déclenchera
une erreur).

   creat()
creat()  est équivalent à open() avec l'attribut flags égal à O_CREAT |
**O_WRONLY**  | O_TRUNC.

   openat()
L'appel système openat() fonctionne de la même façon  que  open(),  les
différences étant décrites ici.

Si  le  chemin  donné  dans pathname est relatif, il est interprété par
rapport au répertoire auquel le descripteur de fichier dirfd fait réfé‐
rence  (et  non  par  rapport au répertoire courant du processus, comme
pour open()).

Si pathname est un chemin relatif, et si dirfd  a  la  valeur  spéciale
AT_FDCWD,  alors pathname est interprété par rapport au répertoire cou‐
rant du processus appelant, comme dans open().

Si pathname est un chemin absolu, dirfd est ignoré.

VALEUR RENVOYÉE
open(), openat() et creat() renvoient le nouveau descripteur de fichier
s'ils  réussissent,  ou -1 s'ils échouent, auquel cas errno contient le
code d'erreur.

ERREURS
open(), openat() et creat()  peuvent  échouer  avec  les  erreurs  sui‐
vantes :

EACCES L'accès  demandé  au  fichier  est interdit, ou la permission de
parcours pour l'un des répertoires du chemin pathname est  refu‐
sée,  ou  le fichier n'existe pas encore et le répertoire parent
ne permet pas l'écriture. (Consultez aussi path_resolution(7).)

EDQUOT Si O_CREAT est indiqué, le fichier n'existe pas et le  quota  de
blocs  de  disque ou d'inœuds de l'utilisateur sur le système de
fichiers a été atteint.

EEXIST pathname existe déjà et O_CREAT et O_EXCL ont été indiqués.

EFAULT pathname pointe en‐dehors de l'espace d'adressage accessible.

EFBIG  Consultez EOVERFLOW.

EINTR  Pendant qu'il était bloqué en attente de l'ouverture d'un  péri‐
phérique  lent  (par  exemple,  une  FIFO ;  consultez fifo(7)),
l'appel a été interrompu par un gestionnaire de signal ; consul‐
tez signal(7).

EINVAL Le  système de fichiers ne gère pas l’attribut O_DIRECT. Consul‐
tez NOTES pour de plus amples renseignements.

EINVAL Valeur incorrecte dans flags.

EINVAL O_TMPFILE a été indiqué dans flags, mais ni O_WRONLY  ni  O_RDWR
n’ont été indiqués.

EISDIR Une  écriture  a été demandée alors que pathname correspond à un
répertoire (en fait, O_WRONLY ou O_RDWR ont été demandés).

EISDIR pathname fait référence à un répertoire existant,  O_TMPFILE  et
soit  O_WRONLY,  soit  O_RDWR, ont été indiqués dans flags, mais
cette version du noyau ne fournit pas la  fonctionnalité  O_TMP‐
FILE.

ELOOP  Trop de liens symboliques ont été rencontrés en parcourant path‐
name.

ELOOP  pathname était un lien symbolique, et flags indiquait O_NOFOLLOW
mais pas O_PATH.

EMFILE Le processus a déjà ouvert le nombre maximal de fichiers.

ENAMETOOLONG
pathname est trop long.

ENFILE La  limite  du nombre total de fichiers ouverts sur le système a
été atteinte.

ENODEV pathname correspond à un fichier spécial et  il  n'y  a  pas  de
périphérique  correspondant. (Ceci est un bogue du noyau Linux ;
dans cette situation, ENXIO devrait être renvoyé.)

ENOENT O_CREAT est absent et le fichier n'existe pas. Ou un  répertoire
du  chemin  d'accès pathname n'existe pas, ou est un lien symbo‐
lique pointant nulle part.

ENOENT pathname fait référence à un répertoire inexistant, O_TMPFILE et
soit  O_WRONLY,  soit  O_RDWR, ont été indiqués dans flags, mais
cette version du noyau ne fournit pas la  fonctionnalité  O_TMP‐
FILE.

ENOMEM Pas assez de mémoire pour le noyau.

ENOSPC pathname  devrait  être  créé  mais le périphérique concerné n'a
plus assez de place pour un nouveau fichier.

ENOTDIR
Un élément du chemin d'accès pathname n'est pas  un  répertoire,
ou  l'attribut  O_DIRECTORY est utilisé et pathname n'est pas un
répertoire.

ENXIO  O_NONBLOCK | O_WRONLY est indiqué, le fichier est une FIFO et le
processus  n'a  pas  de fichier ouvert en lecture. Ou le fichier
est un nœud spécial et il n'y a pas de  périphérique  correspon‐
dant.

EOPNOTSUPP
Le système de fichiers contenant pathname ne prend pas en charge
**O_TMPFILE** .

EOVERFLOW
pathname fait référence à un  fichier  ordinaire  qui  est  trop
grand pour être ouvert. Cela arrive quand une application compi‐
lée sur  une  plate-forme  32 bits  sans  -D_FILE_OFFSET_BITS=64
essaie  d'ouvrir  un  fichier  dont  la taille dépasse (2<<31)-1
bits ; consultez également O_LARGEFILE ci-dessus. C'est l'erreur
spécifiée  par  POSIX.1-2001 ;  dans  les noyaux antérieurs à la
version 2.6.24, Linux fournissait l'erreur EFBIG dans ce cas.

EPERM  L'attribut O_NOATIME est indiqué, mais l'UID effectif de l'appe‐
lant  n'est  pas le propriétaire du fichier, et l'appelant n'est
pas privilégié (CAP_FOWNER).

EROFS  Un accès en écriture est demandé alors que pathname  réside  sur
un système de fichiers en lecture seule.

ETXTBSY
On  a  demandé  une  écriture alors que pathname correspond à un
fichier exécutable actuellement utilisé.

EWOULDBLOCK
L'attribut O_NONBLOCK est indiqué, et un bail  incompatible  est
détenu sur le fichier (consultez fcntl(2)).

Les  erreurs  supplémentaires  suivantes  peuvent également se produire
pour openat() :

EBADF  dirfd n'est pas un descripteur de fichier valable.

ENOTDIR
pathname est relatif, et le descripteur  de  fichier  dirfd  est
associé à un fichier, pas à un répertoire.

VERSIONS
openat()  a été ajouté au noyau Linux dans sa version 2.6.16 ; la glibc
le gère depuis la version 2.4.

CONFORMITÉ
open(), creat() : SVr4, 4.3BSD, POSIX.1-2001, POSIX.1-2008.

openat() : POSIX.1-2008.

Les attributs O_DIRECT, O_NOATIME, O_PATH et O_TMPFILE sont spécifiques
à Linux. _GNU_SOURCE doit être définie pour obtenir leurs définitions.

Les  attributs  O_CLOEXEC, O_DIRECTORY et O_NOFOLLOW ne sont pas spéci‐
fiés  dans  POSIX.1-2001,  mais  le  sont  dans  POSIX.1-2008.   Depuis
glibc 2.12, leurs définitions peuvent être obtenues en définissant soit
_POSIX_C_SOURCE avec une valeur supérieure ou  égale  à  200809L,  soit
_XOPEN_SOURCE   avec  une  valeur  supérieure  ou  égale  à  700.  Dans
glibc 2.11 et les versions précédentes, les  définitions  peuvent  être
obtenues en définissant _GNU_SOURCE.

