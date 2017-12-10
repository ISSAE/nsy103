SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic

EXECUTABLES=			\
		msgctl		\
		msgrcv		\
		msgsnd		\
		shmctl		\
		shmread		\
		shmwrite	\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}
