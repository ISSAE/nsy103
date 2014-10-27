SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic

EXECUTABLES=				\
		exemple_msgctl		\
		exemple_msgrcv		\
		exemple_msgsnd		\
		exemple_shmctl		\
		exemple_shmread		\
		exemple_shmwrite	\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}
