	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/sem.h>
	#include <sys/shm.h>

	#define LG_CHAINE	256

	typedef union semun {
		int                 val;
		struct   semid_ds * buffer;
		unsigned short int * table;
	} semun_t;	

	int
main (int argc, char * argv [])
{
	key_t         key;
	int           sem;
	int           shm;
	struct sembuf sembuf;
	semun_t       u_semun;
	char *        chaine = NULL;
	unsigned short table [1];
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s fichier_clé \n", argv [0]);
		exit (1);
	}
	if ((key = ftok (argv [1], 0)) == -1) {
		perror ("ftok");
		exit (1);
	}
	if ((shm = shmget (key, LG_CHAINE, IPC_CREAT | 0600)) == -1) {
		perror ("shmget");
		exit (1);
	}
	if ((chaine = shmat (shm, NULL, 0)) == NULL) {
		perror ("shmat");
		exit (1);
	}
	if ((sem = semget (key, 1, 0)) == -1) {
		if ((sem = semget (key, 1, IPC_CREAT | IPC_EXCL | 0600)) == -1) {
			perror ("semget");
			exit (1);
		}
		chaine [0] = '\0';
		table [0] = 1;
		u_semun . table = table;
		if (semctl (sem, 0, SETALL, u_semun) < 0)
			perror ("semctl");
	}
	
	sembuf . sem_num = 0;
	sembuf . sem_op  = -1;
	sembuf . sem_flg = SEM_UNDO;
	if (semop (sem, & sembuf, 1) < 0) {
		perror ("semop");
		exit (1);
	}
	fprintf (stdout, "> ");
	fgets (chaine, LG_CHAINE, stdin);
	
	sembuf . sem_op = 1;
	if (semop (sem, & sembuf, 1) < 0) {
		perror ("semop");
		exit (1);
	}
	return (0);
}

