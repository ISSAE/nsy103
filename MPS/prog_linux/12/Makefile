SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g -D_REENTRANT -lpthread

EXECUTABLES=	exemple_condition	\
		exemple_create		\
		exemple_join		\
		exemple_mutex		\
		exemple_semaphores	\
		exemple_signaux		\


all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}
