SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_boucle		\
		exemple_get_priority	\
		exemple_getpriority	\
		exemple_getscheduler	\
		exemple_nice		\
		exemple_ordonnancement	\
		exemple_setscheduler	\
		exemple_status		\


all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}
